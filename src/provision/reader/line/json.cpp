
#include "json.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;
using namespace Tesca::Storage;

namespace
{
	struct	Literal
	{
		const char*				name;
		Glay::Int32u			length;
		Tesca::Storage::Variant	value;
	};

	static Literal	literals[] =
	{
		{"false",	5,	Tesca::Storage::Variant (false)},
		{"null",	4,	Tesca::Storage::Variant::empty},
		{"true",	4,	Tesca::Storage::Variant (true)},
		{0, 		0,	Tesca::Storage::Variant::empty}
	};
}

namespace	Tesca
{
	namespace	Provision
	{
		JSONLineReader::JSONLineReader (Pipe::IStream* input, const Lookup& lookup, const Config& config) :
			LineReader (input, 1024 * 10),
			lookup (lookup),
			row (lookup.count ())
		{
			string	member (config.get ("member", ""));
			string	root (config.get ("root", "row"));

			for (auto i = root.begin (); i != root.end (); ++i)
				this->lookup.next (*i);

			this->member = member.length () > 0 ? member[0] : '.';
		}

		const Row&	JSONLineReader::current () const
		{
			return this->row;
		}

		bool	JSONLineReader::parse (const char* line, Int32u length)
		{
			Cursor	cursor;

			this->row.clear ();			

			cursor.buffer = line;
			cursor.length = length;

			return this->readValue (&cursor);
		}

		bool	JSONLineReader::readCharacter (Cursor* cursor, char expected)
		{
			while (cursor->length > 0 && *cursor->buffer <= ' ')
			{
				++cursor->buffer;
				--cursor->length;
			}

			if (cursor->length < 1 || *cursor->buffer != expected)
				return false;

			++cursor->buffer;
			--cursor->length;

			return true;
		}

		bool	JSONLineReader::readValue (Cursor* cursor)
		{
			char		buffer[16];
			bool		comma;
			Int32u		field;
			Int32u		index;
			Int32u		length;
			Float64		number;
			const char*	start;

			while (cursor->length > 0 && *cursor->buffer <= ' ')
			{
				++cursor->buffer;
				--cursor->length;
			}

			if (cursor->length < 1)
				return false;

			switch (*cursor->buffer)
			{
				case '"':
					if (--cursor->length < 1)
						return false;

					for (start = ++cursor->buffer; cursor->length > 0 && *cursor->buffer != '"'; )
					{
						++cursor->buffer;
						--cursor->length;					
					}

					if (cursor->length < 1)
						return false;

					if (this->lookup.fetch (&field))
						this->row.set (field, Variant (start, cursor->buffer - start));

					++cursor->buffer;
					--cursor->length;

					return true;

				case '-':
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case '.':
					for (start = cursor->buffer; cursor->length > 0 &&
						((*cursor->buffer == '-') ||
						 (*cursor->buffer >= '0' && *cursor->buffer <= '9') ||
						 (*cursor->buffer == '.')); )
					{
						++cursor->buffer;
						--cursor->length;
					}

					if (!Convert::toFloat (&number, start, cursor->buffer - start))
						return false;

					if (this->lookup.fetch (&field))
						this->row.set (field, Variant (number));

					return true;

				case '[':
					++cursor->buffer;
					--cursor->length;

					index = 0;

					for (comma = false; !this->readCharacter (cursor, ']'); comma = true)
					{
						if (comma && !this->readCharacter (cursor, ','))
							return false;

						length = Convert::toString (buffer, sizeof (buffer) / sizeof (*buffer), index++);

						if (length < 1)
							return false;

						this->lookup.enter ();
						this->lookup.next (this->member);

						for (Int32u i = 0; i < length; ++i)
							this->lookup.next (buffer[i]);

						if (!this->readValue (cursor))
						{
							this->lookup.leave ();

							return false;
						}

						this->lookup.leave ();
					}

					return true;

				case '{':
					++cursor->buffer;
					--cursor->length;

					for (comma = false; !this->readCharacter (cursor, '}'); comma = true)
					{
						if (comma && !this->readCharacter (cursor, ','))
							return false;

						if (!this->readCharacter (cursor, '"'))
							return false;

						this->lookup.enter ();
						this->lookup.next (this->member);

						for (start = cursor->buffer; cursor->length > 0 && *cursor->buffer != '"'; )
						{
							this->lookup.next (*cursor->buffer);

							++cursor->buffer;
							--cursor->length;
						}

						if (!this->readCharacter (cursor, '"') ||
						    !this->readCharacter (cursor, ':') ||
						    !this->readValue (cursor))
						{
							this->lookup.leave ();

							return false;
						}

						this->lookup.leave ();
					}

					return true;

				case 'f':
				case 'n':
				case 't':
					for (start = cursor->buffer; cursor->length > 0 && *cursor->buffer >= 'a' && *cursor->buffer <= 'z'; )
					{
						++cursor->buffer;
						--cursor->length;
					}

					length = cursor->buffer - start;

					for (auto current = literals; current->name != 0; ++current)
					{
						if (current->length == length && memcmp (current->name, start, length * sizeof (*current->name)) == 0)
						{
							if (this->lookup.fetch (&field))
								this->row.set (field, current->value);

							return true;
						}
					}

					return false;

				default:
					return false;
			}
		}
	}
}

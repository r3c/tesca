
#include "json.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
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
		JSONLineReader::JSONLineReader (SeekIStream* input, const Lookup& lookup, const Config& config) :
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
			char*		buffer;
			bool		escape;
			Int32u		field;
			Int32u		index;
			char		key[16];
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
				// Parse JSON string literal
				case '"':
					if (--cursor->length < 1)
						return false;

					escape = false;

					for (start = ++cursor->buffer; cursor->length > 0 && *cursor->buffer != '"'; )
					{
						if (*cursor->buffer == '\\' && cursor->length > 1)
						{
							++cursor->buffer;
							--cursor->length;

							escape = true;
						}

						++cursor->buffer;
						--cursor->length;
					}

					if (cursor->length < 1)
						return false;

					if (this->lookup.fetch (&field))
					{
						// String contains at least one escaped character which
						// must be resolved before it's stored in current row
						if (escape)
						{
							buffer = static_cast<char*> (malloc ((cursor->buffer - start - 1) * sizeof (*buffer)));
							length = 0;

							if (!buffer)
								return false;

							while (start < cursor->buffer)
							{
								if (*start == '\\' && start + 1 < cursor->buffer)
									++start;

								buffer[length++] = *start++;
							}

							this->row.set (field, Variant (buffer, length).keep ());

							free (buffer);
						}

						// String has no escapes and can be stored as is
						else
							this->row.set (field, Variant (start, cursor->buffer - start));
					}

					++cursor->buffer;
					--cursor->length;

					return true;

				// Parse JSON number literal
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

				// Parse JSON array
				case '[':
					++cursor->buffer;
					--cursor->length;

					index = 0;

					for (bool comma = false; !this->readCharacter (cursor, ']'); comma = true)
					{
						if (comma && !this->readCharacter (cursor, ','))
							return false;

						length = Convert::toString (key, sizeof (key) / sizeof (*key), index++);

						if (length < 1)
							return false;

						this->lookup.enter ();
						this->lookup.next (this->member);

						for (Int32u i = 0; i < length; ++i)
							this->lookup.next (key[i]);

						if (!this->readValue (cursor))
						{
							this->lookup.leave ();

							return false;
						}

						this->lookup.leave ();
					}

					return true;

				// Parse JSON object
				case '{':
					++cursor->buffer;
					--cursor->length;

					for (bool comma = false; !this->readCharacter (cursor, '}'); comma = true)
					{
						if (comma && !this->readCharacter (cursor, ','))
							return false;

						if (!this->readCharacter (cursor, '"'))
							return false;

						this->lookup.enter ();
						this->lookup.next (this->member);

						for (start = cursor->buffer; cursor->length > 0 && *cursor->buffer != '"'; )
						{
							if (*cursor->buffer == '\\' && cursor->length > 1)
							{
								++cursor->buffer;
								--cursor->length;
							}

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

				// Parse "false", "null" or "true" literal constant
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

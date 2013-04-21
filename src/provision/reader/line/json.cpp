
#include "json.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;
using namespace Tesca::Storage;

namespace
{
	struct	Literal
	{
		const char*					name;
		Glay::Int32u				length;
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
			LineReader (input),
			lookup (lookup),
			root (config.get ("root", "json")),
			row (lookup.count ())
		{
		}

		const Row&	JSONLineReader::current () const
		{
			return this->row;
		}

		bool	JSONLineReader::parse (const char* line, Int32u length)
		{
			Cursor	cursor;

			this->prefix.seekp (0);
			this->prefix << this->root;
			this->row.clear ();			

			cursor.buffer = line;
			cursor.length = length;

			return this->readValue (&cursor, this->prefix);
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

		bool	JSONLineReader::readValue (Cursor* cursor, stringstream& prefix)
		{
			bool		comma;
			Int32u		index;
			Int32u		key;
			Int32u		length;
			Float64		number;
			const char*	start;
			streampos	tip;

			while (cursor->length > 0 && *cursor->buffer <= ' ')
			{
				++cursor->buffer;
				--cursor->length;
			}

			if (cursor->length < 1)
				return false;

			tip = prefix.tellp ();

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

					if (this->lookup.find (prefix.str (), &key))
						this->row.set (key, Variant (start, cursor->buffer - start));

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

					if (!Convert::toFloat64 (&number, start, cursor->buffer - start))
						return false;

					if (this->lookup.find (prefix.str (), &key))
						this->row.set (key, Variant (number));

					return true;

				case '[':
					++cursor->buffer;
					--cursor->length;

					index = 0;

					for (comma = false; !this->readCharacter (cursor, ']'); comma = true)
					{
						if (comma && !this->readCharacter (cursor, ','))
							return false;

						prefix << '.' << index++;

						if (!this->readValue (cursor, prefix))
							return false;

						prefix.seekp (tip);
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

						prefix << '.';

						for (start = cursor->buffer; cursor->length > 0 && *cursor->buffer != '"'; )
						{
							prefix << *cursor->buffer;

							++cursor->buffer;
							--cursor->length;
						}

						if (!this->readCharacter (cursor, '"'))
							return false;

						if (!this->readCharacter (cursor, ':') || !this->readValue (cursor, prefix))
							return false;

						prefix.seekp (tip);
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
							if (this->lookup.find (prefix.str (), &key))
								this->row.set (key, current->value);

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

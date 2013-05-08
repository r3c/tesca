
#include "csv.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;
using namespace Tesca::Storage;

namespace
{
	static const char	TYPE_BLANK = 1;
	static const char	TYPE_QUOTE = 2;
	static const char	TYPE_SPLIT = 3;
}

namespace	Tesca
{
	namespace	Provision
	{
		CSVLineReader::CSVLineReader (Pipe::IStream* input, const Lookup& lookup, const Config& config) :
			LineReader (input, 1024 * 10),
			row (lookup.count ())
		{
			const char*	buffer;
			string		characters;
			string		headers;
			Int32u		index;
			Int32u		length;
			Int32u		value;

			// Read special character types from configuration
			this->types = static_cast<char*> (calloc (1 << (sizeof (*this->types) * 8), sizeof (*this->types)));

			characters = config.get ("blanks", "\n\r\t ");

			for (auto i = characters.begin (); i != characters.end (); ++i)
				this->types[(Int32s)*i] = TYPE_BLANK;

			characters = config.get ("quotes", "\"");

			for (auto i = characters.begin (); i != characters.end (); ++i)
				this->types[(Int32s)*i] = TYPE_QUOTE;

			characters = config.get ("splits", ",");

			for (auto i = characters.begin (); i != characters.end (); ++i)
				this->types[(Int32s)*i] = TYPE_SPLIT;

			// Read headers from configuration or use default
			if (config.get ("headers", &headers))
			{
				if (headers.length () > 0)
				{
					buffer = headers.c_str ();
					length = headers.length ();
				}
				else if (!this->read (&buffer, &length))
				{
					buffer = 0;
					length = 0;
				}

				this->split (buffer, length, [&] (Int32u index, const char* buffer, Int32u length)
				{
					string	key (buffer, length);
					Int32u	value;

					if (lookup.find (key.c_str (), &value))
					{
						if (index >= this->mapping.size ())
							this->mapping.resize (index + 1);

						this->mapping[index] = value + 1;
					}
				});
			}
			else
			{
				value = 0;

				for (auto i = lookup.begin (); i != lookup.end (); ++i)
				{
					if (Convert::toInteger (&index, i->c_str (), i->length ()))
					{
						if (index >= this->mapping.size ())
							this->mapping.resize (index + 1);

						this->mapping[index] = value + 1;
					}

					++value;
				}
			}
		}

		const Row&	CSVLineReader::current () const
		{
			return this->row;
		}

		bool	CSVLineReader::parse (const char* line, Int32u length)
		{
			this->row.clear ();

			this->split (line, length, [&] (Int32u index, const char* buffer, Int32u length)
			{
				Int32u	key;

				key = index < this->mapping.size () ? this->mapping[index] : 0;

				if (key != 0)
					this->row.set (key - 1, Variant (buffer, length));
			});

			return true;
		}

		void	CSVLineReader::split (const char* line, Int32u length, Callback callback)
		{
			Int32u		index;
			const char*	skip;
			const char*	start;
			const char*	stop;

			start = line;

			for (index = 0; ; ++index)
			{
				// Skip leading characters to ignore
				while (length > 0 && this->types[(Int32u)*start] == TYPE_BLANK)
				{
					--length;
					++start;
				}

				// Field is enclosed between quotes
				if (length > 0 && this->types[(Int32u)*start] == TYPE_QUOTE)
				{
					--length;
					++start;

					stop = start;

					while (true)
					{
						while (length > 0 && this->types[(Int32u)*stop] != TYPE_QUOTE)
						{
							--length;
							++stop;
						}

						// FIXME: resolve escaped quotes
						if (length < 2 || this->types[(Int32u)*(stop + 1)] != TYPE_QUOTE)
							break;

						length -= 2;
						stop += 2;
					}

					callback (index, start, stop - start);

					while (length > 0 && this->types[(Int32u)*stop] != TYPE_SPLIT)
					{
						--length;
						++stop;
					}

					start = stop;
				}

				// Field is a simple unescaped string
				else
				{
					skip = start;

					for (stop = start; length > 0; stop = skip)
					{
						for (skip = stop; length > 0 && this->types[(Int32u)*skip] == TYPE_BLANK; ++skip)
							--length;

						if (length == 0 || this->types[(Int32u)*skip] == TYPE_SPLIT)
							break;

						--length;
						++skip;						
					}

					callback (index, start, stop - start);

					start = skip;
				}

				if (length == 0)
					break;

				--length;
				++start;
			}
		}
	}
}


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
			LineReader (input),
			row (lookup.count ())
		{
			const char*	buffer;
			string		headers;
			Int32u		index;
			Int32u		length;

			// Read special character types from configuration
			this->types = static_cast<char*> (calloc (1 << (sizeof (*this->types) * 8), sizeof (*this->types)));

			for (buffer = config.get ("blanks", "\n\r\t ").c_str (); *buffer; )
				this->types[(Int32u)*buffer++] = TYPE_BLANK;

			for (buffer = config.get ("quotes", "\"").c_str (); *buffer; )
				this->types[(Int32u)*buffer++] = TYPE_QUOTE;

			for (buffer = config.get ("splits", ",").c_str (); *buffer; )
				this->types[(Int32u)*buffer++] = TYPE_SPLIT;

			// Read headers from configuration or use default
			if (config.get ("headers", &headers))
			{
				if (headers.length () > 0)
				{
					buffer = headers.c_str ();
					length = headers.length ();
				}
				else if (!this->fetch (&buffer, &length))
				{
					buffer = 0;
					length = 0;
				}

				this->split (buffer, length, [&] (Int32u index, const char* buffer, Int32u length)
				{
					Int32u	target;

					if (lookup.find (string (buffer, length), &target))
						this->mapping[index] = target;
				});
			}
			else
			{
				for (auto i = lookup.begin (); i != lookup.end (); ++i)
				{
					if (Convert::toInt32u (&index, i->first.c_str (), i->first.length ()))
						this->mapping[index] = i->second;
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
				auto	field = this->mapping.find (index);

				if (field != this->mapping.end ())
					this->row.set (field->second, Variant (buffer, length));
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

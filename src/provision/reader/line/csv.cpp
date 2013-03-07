
#include "csv.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;

namespace
{
	static const char	TYPE_QUOTE = 1;
	static const char	TYPE_SPLIT = 2;
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

			for (buffer = config.get ("quotes", "\"").c_str (); *buffer; )
				this->types[(Int32u)*buffer++] = TYPE_QUOTE;

			for (buffer = config.get ("splits", ",").c_str (); *buffer; )
				this->types[(Int32u)*buffer++] = TYPE_SPLIT;

			// Read headers from configuration or file or default
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
			const char*	start;
			const char*	stop;

			index = 0;
			start = line;
			stop = line;

			while (length-- > 0)
			{
				switch (this->types[(Int32u)*stop])
				{
//					case TYPE_QUOTE:
//						break;

					case TYPE_SPLIT:
						callback (index++, start, stop - start);

						start = stop + 1;

						break;
				}

				++stop;
			}

			callback (index, start, stop - start);
		}
	}
}

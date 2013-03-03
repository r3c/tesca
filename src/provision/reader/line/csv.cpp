
#include "csv.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;

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

			// Read split characters from configuration
			this->splits = static_cast<char*> (calloc (1 << (sizeof (*this->splits) * 8), sizeof (*this->splits)));

			for (buffer = config.get ("splits", ",").c_str (); *buffer; )
				this->splits[(Int32u)*buffer++] = 1;

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

		void	CSVLineReader::parse (const char* line, Int32u length)
		{
			this->row.clear ();

			this->split (line, length, [&] (Int32u index, const char* buffer, Int32u length)
			{
				auto	field = this->mapping.find (index);

				if (field != this->mapping.end ())
					this->row.set (field->second, Variant (buffer, length));
			});
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
				if (this->splits[(Int32u)*stop])
				{
					callback (index++, start, stop - start);

					start = stop + 1;
				}

				++stop;
			}

			callback (index, start, stop - start);
		}
	}
}

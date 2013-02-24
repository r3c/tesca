
#include "csv.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;

namespace	Tesca
{
	CSVLineReader::CSVLineReader (Pipe::IStream* input, const Fields* fields, bool headers, char separator) :
		LineReader (input),
		row (fields->size ()),
		separator (separator)
	{
		const char*	buffer;
		Int32u		index;
		Int32u		length;

		if (headers && this->fetch (&buffer, &length))
		{
			this->split (buffer, length, [&] (Int32u index, const char* buffer, Int32u length)
			{
				auto	field = fields->find (string (buffer, length));

				if (field != fields->end ())
					this->lookup[index] = field->second;
			});
		}
		else
		{
			for (auto i = fields->begin (); i != fields->end (); ++i)
			{
				if (Convert::toInt32u (&index, i->first.c_str (), i->first.length ()))
					this->lookup[index] = i->second;
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
			auto	field = this->lookup.find (index);

			if (field != this->lookup.end ())
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
			if (*stop == this->separator)
			{
				callback (index++, start, stop - start);

				start = stop + 1;
			}

			++stop;
		}

		callback (index, start, stop - start);
	}
}

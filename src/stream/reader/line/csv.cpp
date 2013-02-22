
#include "csv.hpp"

#include <sstream>
#include <string>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	CSVLineReader::CSVLineReader (Pipe::IStream* input, const Fields* fields, bool headers, char separator) :
		LineReader (input),
		row (fields->size ()),
		separator (separator)
	{
		const char*		buffer;
		Int32u			index;
		Int32u			length;
		stringstream	stream;

		if (headers && this->read (&buffer, &length))
		{
			this->split (buffer, length, [&] (Int32u index, const char* value, Int32u length)
			{
				Fields::const_iterator	field;
				string					name (value, length);

				field = fields->find (value);

				if (field != fields->end ())
					this->lookup[index] = field->second;
			});
		}
		else
		{
			for (auto i = fields->begin (); i != fields->end (); ++i)
			{
				stream.str (i->first);
				stream >> index;

				if (!stream.fail ())
					this->lookup[index] = i->second;

				stream.clear ();
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

		this->split (line, length, [&] (Int32u index, const char* value, Int32u length)
		{
			auto	field = this->lookup.find (index);

			if (field != this->lookup.end ())
				this->row[field->second] = Variant (value, length);
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


#include "csv.hpp"

#include <sstream>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	CSVLineReader::CSVLineReader (Pipe::IStream* input, const Fields* fields, bool headers, char separator) :
		LineReader (input),
		row (fields->size ()),
		separator (separator)
	{
		stringstream	buffer;
		Int32u			index;

		if (headers && this->read (buffer))
		{
			this->split (buffer.str (), [&] (Int32u index, const string& value)
			{
				Fields::const_iterator	field;

				field = fields->find (value);

				if (field != fields->end ())
					this->lookup[index] = field->second;
			});
		}
		else
		{
			for (auto i = fields->begin (); i != fields->end (); ++i)
			{
				buffer.str (i->first);
				buffer >> index;

				if (!buffer.fail ())
					this->lookup[index] = i->second;

				buffer.clear ();
			}
		}
	}

	const Row&	CSVLineReader::current () const
	{
		return this->row;
	}

	void	CSVLineReader::parse (const string& line)
	{
		this->row.clear ();

		this->split (line, [&] (Int32u index, const string& value)
		{
			auto	field = this->lookup.find (index);

			if (field != this->lookup.end ())
				this->row[field->second] = Variant (value);
		});
	}

	void	CSVLineReader::split (const string& line, const Callback& callback)
	{
		Int32u	index;
		Int32u	start;

		index = 0;
		start = 0;

		for (Int32u i = 0; i < line.length (); ++i)
		{
			if (line[i] == this->separator)
			{
				callback (index++, line.substr (start, i - start));

				start = i + 1;
			}
		}

		callback (index, line.substr (start));
	}
}


#include "csv.hpp"

#include <sstream>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	CSVLineReader::CSVLineReader (Pipe::IStream* input, const Fields* fields, bool headers) :
		LineReader (input),
		row (fields->size ())
	{
		stringstream			buffer;
		Int32u					column;
		Fields::const_iterator	field;

		if (headers && this->read (buffer))
		{
/*
			column = 0;

			for_each (header in buffer)
			{
				field = fields.find (header);

				if (field != fields.end ())
					this->lookup[column] = field->second;

				++column;
			}
*/
		}
		else
		{
			for (auto i = fields->begin (); i != fields->end (); ++i)
			{
				buffer.str (i->first);
				buffer >> column;

				if (!buffer.fail ())
					this->lookup[column] = i->second;

				buffer.clear ();
			}
		}
	}

	const Row&	CSVLineReader::current () const
	{
		return this->row;
	}

	void	CSVLineReader::parse (const std::string& line)
	{
		this->row.clear ();

		// FIXME: parse CSV, fill row[this->lookup[column]]
	}
}

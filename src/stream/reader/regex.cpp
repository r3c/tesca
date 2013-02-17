
#include "regex.hpp"

#include <sstream>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	RegexReader::RegexReader (const Fields* fields, const string& pattern) :
		fields (fields),
		regex (pattern),
		row (fields->size ())
	{
	}

	const Row&	RegexReader::current () const
	{
		return this->row;
	}

	bool	RegexReader::next ()
	{
		stringstream			buffer;
		Fields::const_iterator	field;
		string					identifier;
		Int32u					index;
		string					line; // FIXME: read line from somewhere
		smatch					match;

		this->row.clear ();

		if (regex_match (line, match, this->regex))
		{
			index = 0;

			for (auto i = match.begin (); i != match.end (); ++i)
			{
				buffer << index;
				buffer >> identifier;
				buffer.clear ();

				field = this->fields->find (identifier);

				if (field != this->fields->end ())
					this->row[field->second] = Variant (*i);

				++index;
			}
		}

		return true;
	}
}

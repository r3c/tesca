
#include "regex.hpp"

#include <sstream>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	RegexReader::RegexReader (const Fields* fields, const string& pattern) :
		regex (pattern),
		row (fields->size ())
	{
		stringstream	buffer;
		Int32u			group;

		for (auto i = fields->begin (); i != fields->end (); ++i)
		{
			buffer.str (i->first);
			buffer >> group;

			if (!buffer.fail ())
				this->matches[group] = i->second;

			buffer.clear ();
		}
	}

	const Row&	RegexReader::current () const
	{
		return this->row;
	}

	bool	RegexReader::next ()
	{
		Int32u					group;
		Matches::const_iterator	item;
		string					line; // FIXME: read line from somewhere
		smatch					match;

		this->row.clear ();

		if (regex_match (line, match, this->regex))
		{
			group = 0;

			for (auto i = match.begin (); i != match.end (); ++i)
			{
				item = this->matches.find (group);

				if (item != this->matches.end ())
					this->row[item->second] = Variant (*i);

				++group;
			}
		}

		return true;
	}
}

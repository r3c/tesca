
#include "regex.hpp"

#include <sstream>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	RegexLineReader::RegexLineReader (Pipe::IStream* input, const Fields* fields, const string& pattern) :
		LineReader (input),
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
				this->lookup[group] = i->second;

			buffer.clear ();
		}
	}

	const Row&	RegexLineReader::current () const
	{
		return this->row;
	}

	void	RegexLineReader::parse (const std::string& line)
	{
		smatch	match;

		this->row.clear ();

		if (regex_match (line, match, this->regex))
		{
			for (auto i = this->lookup.begin (); i != this->lookup.end (); ++i)
			{
				if (i->first < match.size ())
					this->row[i->second] = Variant (match[i->first]);
			}
		}
	}
}

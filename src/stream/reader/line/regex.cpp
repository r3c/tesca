
#include "regex.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;

namespace	Tesca
{
	RegexLineReader::RegexLineReader (Pipe::IStream* input, const Fields* fields, const Config& config) :
		LineReader (input),
		regex ("FIXME"),
		row (fields->size ())
	{
		Int32u	group;

		for (auto i = fields->begin (); i != fields->end (); ++i)
		{
			if (Convert::toInt32u (&index, i->first.c_str (), i->first.length ()))
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
					this->row.set (i->second, Variant (match[i->first]));
			}
		}
	}
}

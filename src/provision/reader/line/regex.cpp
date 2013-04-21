
#include "regex.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Provision
	{
		RegexLineReader::RegexLineReader (Pipe::IStream* input, const Lookup& lookup, const Config&) :
			LineReader (input),
			regex ("FIXME"),
			row (lookup.count ())
		{
			Int32u	group;

			for (auto i = lookup.begin (); i != lookup.end (); ++i)
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

		bool	RegexLineReader::parse (const std::string& line)
		{
			smatch	match;

			this->row.clear ();

			if (!regex_match (line, match, this->regex))
				return false;

			for (auto i = this->lookup.begin (); i != this->lookup.end (); ++i)
			{
				if (i->first < match.size ())
					this->row.set (i->second, Variant (match[i->first]));
			}

			return true;
		}
	}
}

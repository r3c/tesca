
#include "regex.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Glay::System;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Provision
	{
		RegexLineReader::RegexLineReader (SeekIStream* input, Lookup const& lookup, Config const&) :
			LineReader (input),
			regex ("FIXME"),
			row (lookup.count ())
		{
			Int32u group;

			for (auto i = lookup.begin (); i != lookup.end (); ++i)
			{
				const string& key = *i;

				if (key.length () > 0 && key[0] == '_' && Convert::toInt32u (&index, key.data () + 1, key.length () - 1))
					this->lookup[group] = i->second;

				buffer.clear ();
			}
		}

		Row const& RegexLineReader::current () const
		{
			return this->row;
		}

		bool RegexLineReader::parse (const std::string& line)
		{
			smatch match;

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

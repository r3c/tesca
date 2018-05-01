
#ifndef __TESCA_PROVISION_READER_LINE_REGEX_HPP
#define __TESCA_PROVISION_READER_LINE_REGEX_HPP

#include <map>
#include <regex>
#include "../../../storage/config.hpp"
#include "../../row/array.hpp"
#include "../../lookup.hpp"
#include "../line.hpp"

namespace Tesca
{
	namespace Provision
	{
		class RegexLineReader : public LineReader
		{
			public:
				RegexLineReader (RegexLineReader const&);
				RegexLineReader (Glay::Pipe::SeekIStream*, Lookup const&, Storage::Config const&);

				RegexLineReader& operator = (RegexLineReader const&);

				virtual Row const& current () const;

			protected:
				virtual bool parse (const std::string&);

			private:
				typedef std::map<Glay::Int32u, Glay::Int32u> Lookup;

				Lookup lookup;
				std::regex regex;
				ArrayRow row;


		};
	}
}

#endif

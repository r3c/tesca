
#ifndef __TESCA_PROVISION_READER_LINE_REGEX_HPP
#define __TESCA_PROVISION_READER_LINE_REGEX_HPP

#include <map>
#include <regex>
#include "../../row/array.hpp"
#include "../../config.hpp"
#include "../../lookup.hpp"
#include "../line.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	RegexLineReader : public LineReader
		{
			public:
				RegexLineReader (const RegexLineReader&);
				RegexLineReader (Glay::Pipe::IStream*, const Lookup&, const Config&);

				RegexLineReader&	operator = (const RegexLineReader&);

				virtual const Row&	current () const;

			protected:
				virtual void	parse (const std::string&);

			private:
				typedef std::map<Glay::Int32u, Glay::Int32u>	Lookup;

				Lookup		lookup;
				std::regex	regex;
				ArrayRow	row;


		};
	}
}

#endif

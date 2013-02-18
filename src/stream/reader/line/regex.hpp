
#ifndef __TESCA_READER_LINE_REGEX_HPP
#define __TESCA_READER_LINE_REGEX_HPP

#include <map>
#include <regex>
#include "../../row/array.hpp"
#include "../line.hpp"

namespace	Tesca
{
	class	RegexLineReader : public LineReader
	{
		public:
			typedef std::map<std::string, Glay::Int32u>	Fields;

			RegexLineReader (const RegexLineReader&);
			RegexLineReader (Glay::Pipe::IStream*, const Fields*, const std::string&);

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

#endif

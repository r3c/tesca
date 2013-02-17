
#ifndef __TESCA_READER_REGEX_HPP
#define __TESCA_READER_REGEX_HPP

#include <map>
#include <regex>
#include <string>
#include "../row/array.hpp"
#include "../reader.hpp"

namespace	Tesca
{
	class	RegexReader : public Reader
	{
		public:
			typedef std::map<std::string, Glay::Int32u>	Fields;

			/**/	RegexReader (const RegexReader&);
			/**/	RegexReader (const Fields*, const std::string&);

			RegexReader&	operator = (const RegexReader&);

			virtual const Row&	current () const;
			virtual bool		next ();

		private:
			typedef std::map<Glay::Int32u, Glay::Int32u>	Matches;

			Matches		matches;
			std::regex	regex;
			ArrayRow	row;


	};
}

#endif

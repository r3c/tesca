
#ifndef __TESCA_EXPRESSION_FORMULA_HPP
#define __TESCA_EXPRESSION_FORMULA_HPP

#include <string>
#include <vector>
#include "parser.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		class	Formula
		{
			public:
				typedef std::vector<const Column*>	Columns;

				Formula (const Formula&);
				Formula ();
				~Formula ();

				Formula&	operator = (const Formula&);

				const Columns&	getColumns () const;
				std::string		getMessage () const;

				bool	parse (Stream::Lookup&, const char*);
				void	reset ();

			private:
				Columns	columns;
				Parser	parser;

		};
	}
}

#endif

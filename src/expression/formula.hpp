
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
				typedef Parser::ErrorEvent			ErrorEvent;

				Formula (const Formula&);
				Formula ();
				~Formula ();

				Formula&	operator = (const Formula&);

				const Columns&		getColumns () const;
				const ErrorEvent&	getError () const;
				ErrorEvent&			getError ();

				bool	parse (Provision::Lookup&, const char*);
				void	reset ();

			private:
				Columns	columns;
				Parser	parser;

		};
	}
}

#endif

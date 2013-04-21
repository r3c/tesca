
#ifndef __TESCA_EXPRESSION_CALCULATOR_HPP
#define __TESCA_EXPRESSION_CALCULATOR_HPP

#include <string>
#include <vector>
#include "parser.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		class	Calculator
		{
			public:
				typedef std::vector<const Arithmetic::Column*>	Columns;
				typedef Parser::Error							Error;

				Calculator (const Calculator&);
				Calculator ();
				~Calculator ();

				Calculator&	operator = (const Calculator&);

				const Columns&	getColumns () const;
				const Error&	getError () const;
				Error&			getError ();

				bool	parse (Provision::Lookup&, const char*);
				void	reset ();

			private:
				Columns	columns;
				Parser	parser;

		};
	}
}

#endif

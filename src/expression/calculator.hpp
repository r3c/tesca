
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
				typedef std::vector<Arithmetic::Column>	Columns;
				typedef Parser::Error					Error;

				Calculator (const Calculator&);
				Calculator ();
				~Calculator ();

				Calculator&	operator = (const Calculator&);

				const Columns&	getColumns () const;
				const Error&	getError () const;
				Error&			getError ();
				Glay::Int32u	getSlots () const;

				bool	parse (Provision::Lookup&, const char*);
				void	reset ();

			private:
				Columns			columns;
				Parser			parser;
				Glay::Int32u	slots;

		};
	}
}

#endif

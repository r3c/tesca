
#ifndef __TESCA_EXPRESSION_FILTER_HPP
#define __TESCA_EXPRESSION_FILTER_HPP

#include <string>
#include "parser.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		class	Filter
		{
			public:
				typedef Parser::Error	Error;

				Filter (const Filter&);
				Filter ();
				~Filter ();

				Filter&	operator = (const Filter&);

				const Arithmetic::Extractor*	getCondition () const;
				const Error&				getError () const;
				Error&						getError ();

				bool	parse (Provision::Lookup&, const char*);
				void	reset ();

			private:
				const Arithmetic::Extractor*	condition;
				Parser						parser;

		};
	}
}

#endif

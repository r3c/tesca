
#ifndef __TESCA_EXPRESSION_SELECT_HPP
#define __TESCA_EXPRESSION_SELECT_HPP

#include <string>
#include "../arithmetic/lookup.hpp"
#include "function.hpp"
#include "lexer.hpp"
#include "parser.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		class	Select
		{
			public:
				Select (const Select&);
				Select ();
				~Select ();

				Select&	operator = (const Select&);

				const Accessor*			getAccessor () const;
				std::string				getMessage () const;

				bool	parse (Lookup&, const char*);
				void	reset ();

			private:
				const Accessor*	accessor;
				Parser			parser;

		};
	}
}

#endif

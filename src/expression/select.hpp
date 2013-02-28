
#ifndef __TESCA_EXPRESSION_SELECT_HPP
#define __TESCA_EXPRESSION_SELECT_HPP

#include <string>
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

				const Accessor*	getCondition () const;
				std::string		getMessage () const;

				bool	parse (Stream::Lookup&, const char*);
				void	reset ();

			private:
				const Accessor*	condition;
				Parser			parser;

		};
	}
}

#endif
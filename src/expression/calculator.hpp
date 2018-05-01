
#ifndef __TESCA_EXPRESSION_CALCULATOR_HPP
#define __TESCA_EXPRESSION_CALCULATOR_HPP

#include <string>
#include <vector>
#include "parser.hpp"

namespace Tesca
{
	namespace Expression
	{
		class Calculator
		{
			public:
				typedef std::vector<Arithmetic::Column> Columns;
				typedef Parser::Error Error;

				Calculator (Calculator const&);
				Calculator ();
				~Calculator ();

				Calculator& operator = (Calculator const&);

				Columns const& getColumns () const;
				Glay::Int32u getSlots () const;

				Error const& onError () const;
				Error& onError ();

				bool parse (Provision::Lookup&, const char*);
				void reset ();

			private:
				Columns columns;
				Parser parser;
				Glay::Int32u slots;

		};
	}
}

#endif

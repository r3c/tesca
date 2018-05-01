
#ifndef __TESCA_EXPRESSION_FILTER_HPP
#define __TESCA_EXPRESSION_FILTER_HPP

#include <string>
#include "parser.hpp"

namespace Tesca
{
	namespace Expression
	{
		class Filter
		{
			public:
				typedef Parser::Error Error;

				Filter (Filter const&);
				Filter ();
				~Filter ();

				Filter& operator = (Filter const&);

				Arithmetic::Extractor const* getCondition () const;

				Error const& onError () const;
				Error& onError ();

				bool parse (Provision::Lookup&, const char*);
				void reset ();

			private:
				Arithmetic::Extractor const* condition;
				Parser parser;

		};
	}
}

#endif

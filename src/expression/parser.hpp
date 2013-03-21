
#ifndef __TESCA_EXPRESSION_PARSER_HPP
#define __TESCA_EXPRESSION_PARSER_HPP

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "../../lib/glay/src/include.hpp"
#include "../provision/lookup.hpp"
#include "aggregator.hpp"
#include "lexer.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		class	Parser
		{
			public:
				typedef Glay::Design::Event<const std::string&>	ErrorEvent;

				Parser (const Parser&);
				Parser ();
				~Parser ();

				Parser&	operator = (const Parser&);

				const ErrorEvent&	getError () const;
				ErrorEvent&			getError ();

				bool	parseAggregator (Lexer&, const Aggregator**);
				bool	parseCharacter (Lexer&, char);
				bool	parseExpression (Lexer&, Provision::Lookup&, const Accessor**);
				bool	parseIdentifier (Lexer&, std::string*);
				bool	parseStatement (Lexer&, Provision::Lookup&, Column**);
				bool	parseValue (Lexer&, Provision::Lookup&, const Accessor**);
				bool	skip (Lexer&);

				void	reset ();

			private:
				typedef std::vector<const Accessor*>	Accessors;
				typedef std::vector<const Column*>		Columns;

				bool	fail (const Lexer&, const std::string&);

				Accessors	accessors;
				Columns		columns;
				ErrorEvent	error;
		};
	}
}

#endif

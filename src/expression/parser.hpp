
#ifndef __TESCA_EXPRESSION_PARSER_HPP
#define __TESCA_EXPRESSION_PARSER_HPP

#include <algorithm>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "../glay/glay.hpp"
#include "../stream/lookup.hpp"
#include "aggregator.hpp"
#include "function.hpp"
#include "lexer.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		class	Parser
		{
			public:
				Parser (const Parser&);
				Parser ();
				~Parser ();

				Parser&	operator = (const Parser&);

				std::string		getMessage () const;

				bool	parseAggregator (Lexer&, const Aggregator**);
				bool	parseCharacter (Lexer&, char);
				bool	parseExpression (Lexer&, Stream::Lookup&, const Accessor**);
				bool	parseIdentifier (Lexer&, std::string*);
				bool	parseStatement (Lexer&, Stream::Lookup&, Column**);
				bool	parseValue (Lexer&, Stream::Lookup&, const Accessor**);
				bool	skip (Lexer&);

				void	reset ();

			private:
				typedef std::vector<const Accessor*>	Accessors;
				typedef std::vector<const Column*>		Columns;

				bool	fail (const Lexer&, const std::string&);

				Accessors			accessors;
				Columns				columns;
				std::stringstream	message;
		};
	}
}

#endif

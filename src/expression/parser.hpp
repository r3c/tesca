
#ifndef __TESCA_EXPRESSION_PARSER_HPP
#define __TESCA_EXPRESSION_PARSER_HPP

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "../../lib/glay/src/include.hpp"
#include "../arithmetic/column.hpp"
#include "../arithmetic/extractor.hpp"
#include "../provision/lookup.hpp"
#include "lexer.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		class	Parser
		{
			public:
				typedef Glay::Design::Event<const std::string&>	Error;

				Parser (const Parser&);
				Parser ();
				~Parser ();

				Parser&	operator = (const Parser&);

				const Error&	getError () const;
				Error&			getError ();

				bool	parseExpression (Lexer&, Provision::Lookup&, Glay::Int32u*, const Arithmetic::Extractor**);
				bool	parseKey (Lexer&, std::string*);
				bool	parseType (Lexer&, Lexer::Lexem, const char*);
				bool	parseValue (Lexer&, Provision::Lookup&, Glay::Int32u*, const Arithmetic::Extractor**);

				void	reset ();

			private:
				typedef std::vector<const Arithmetic::Extractor*>															Extractors;
				typedef std::function<Arithmetic::Extractor* (const Arithmetic::Extractor*, const Arithmetic::Extractor*)>	Generator;
				typedef std::pair<Glay::Int32u, Generator>																	BinaryOp;

				bool	fail (const Lexer&, const std::string&);

				Extractors	extractors;
				Error		error;
		};
	}
}

#endif

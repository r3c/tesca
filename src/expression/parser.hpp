
#ifndef __TESCA_EXPRESSION_PARSER_HPP
#define __TESCA_EXPRESSION_PARSER_HPP

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include "../../lib/glay/src/glay.hpp"
#include "../arithmetic/column.hpp"
#include "../arithmetic/extractor.hpp"
#include "../provision/lookup.hpp"
#include "lexer.hpp"

namespace Tesca
{
	namespace Expression
	{
		class Parser
		{
			public:
				typedef Glay::Design::Event<const std::string&> Error;

				Parser (Parser const&);
				Parser ();
				~Parser ();

				Parser& operator = (Parser const&);

				Error const& onError () const;
				Error& onError ();

				bool parseExpression (Lexer&, Provision::Lookup&, Glay::Int32u*, Arithmetic::Extractor const**);
				bool parseIdentifier (Lexer&, std::string*);
				bool parseLexemType (Lexer&, Lexer::LexemType, const char*);
				bool parseValue (Lexer&, Provision::Lookup&, Glay::Int32u*, Arithmetic::Extractor const**);

				void reset ();

			private:
				typedef std::vector<Arithmetic::Extractor const*> Extractors;
				typedef std::function<Arithmetic::Extractor* (Arithmetic::Extractor const*, Arithmetic::Extractor const*)> Generator;
				typedef std::pair<Glay::Int32u, Generator> BinaryOp;

				bool fail (Lexer const&, const std::string&);

				Extractors extractors;
				Error error;
		};
	}
}

#endif

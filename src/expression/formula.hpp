
#ifndef __TESCA_EXPRESSION_FORMULA_HPP
#define __TESCA_EXPRESSION_FORMULA_HPP

#include <algorithm>
#include <string>
#include <vector>
#include "../arithmetic/column.hpp"
#include "../glay/glay.hpp"
#include "aggregator.hpp"
#include "function.hpp"
#include "lexer.hpp"

namespace	Tesca
{
	class	Formula
	{
		public:
			typedef std::vector<Column*>	Columns;
			typedef std::vector<Reader*>	Readers;

			/**/				Formula (const Formula&);
			/**/				Formula ();
			/**/				~Formula ();

			Formula&			operator = (const Formula&);

			const Columns		getColumns () const;
			const std::string&	getError () const;

			bool				parse (const char*);
			void				reset ();

		private:
			bool	fail (const Lexer&, const std::string&);
			bool	readAggregator (Lexer&, const Aggregator**);
			bool	readCharacter (Lexer&, const char);
			bool	readExpression (Lexer&, Reader**);
			bool	readIdentifier (Lexer&, std::string*);
			bool	readValue (Lexer&, Reader**);
			bool	skip (Lexer&);

			Columns		columns;
			std::string	error;
			Readers		readers;

	};
}

#endif

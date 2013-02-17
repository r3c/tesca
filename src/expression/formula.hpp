
#ifndef __TESCA_EXPRESSION_FORMULA_HPP
#define __TESCA_EXPRESSION_FORMULA_HPP

#include <algorithm>
#include <map>
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
			typedef std::vector<const Accessor*>		Accessors;
			typedef std::vector<const Column*>			Columns;
			typedef std::map<std::string, Glay::Int32u>	Fields;

			Formula (const Formula&);
			Formula ();
			~Formula ();

			Formula&	operator = (const Formula&);

			const Columns&		getColumns () const;
			const std::string&	getError () const;
			const Fields&		getFields () const;

			bool	parse (const char*);
			void	reset ();

		private:
			bool	fail (const Lexer&, const std::string&);
			bool	readAggregator (Lexer&, const Aggregator**);
			bool	readCharacter (Lexer&, const char);
			bool	readExpression (Lexer&, const Accessor**);
			bool	readIdentifier (Lexer&, std::string*);
			bool	readValue (Lexer&, const Accessor**);
			bool	skip (Lexer&);

			Accessors	accessors;
			Columns		columns;
			std::string	error;
			Fields		fields;

	};
}

#endif

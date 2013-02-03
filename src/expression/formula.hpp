
#ifndef __TESCA_EXPRESSION_FORMULA_HPP
#define __TESCA_EXPRESSION_FORMULA_HPP

#include <string>
#include <vector>
#include "../glay/glay.hpp"
#include "../arithmetic/column.hpp"
#include "lexer.hpp"

namespace	Tesca
{
	class	Formula
	{
		public:
			typedef std::vector<Column*>		Columns;
			typedef std::vector<std::string>	Names;

			/**/				Formula (const Formula&);
			/**/				Formula ();
			/**/				~Formula ();

			const Columns		getColumns () const;
			const std::string&	getError () const;
			const Names			getNames () const;

			bool				parse (const char*);
			void				reset ();

		private:
			typedef bool	(Formula::*Reader) (Lexer&, Column**);

			struct	Function
			{
				const char*	name;
				Reader		reader;
			};

			bool	fail (const Lexer&, const std::string&);
			bool	readCharacter (Lexer&, const char);
			bool	readExpression (Lexer&, Column**);
			bool	readFunctionAverage (Lexer&, Column**);
			bool	readFunctionSum (Lexer&, Column**);
			bool	readIdentifier (Lexer&, std::string*);
			bool	readValue (Lexer&, Column**);
			bool	skip (Lexer&);
			Column*	store (Column*);

			static Function	functions[];

			Columns		allocs;
			Columns		columns;
			std::string	error;
			Names		names;

	};
}

#endif

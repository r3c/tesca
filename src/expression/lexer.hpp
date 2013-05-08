
#ifndef __TESCA_EXPRESSION_LEXER_HPP
#define __TESCA_EXPRESSION_LEXER_HPP

#include <sstream>
#include <string>
#include "../../lib/glay/src/include.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		class	Lexer
		{
			public:
				enum	Lexem
				{
					AMPERSAND,
					COLON,
					COMMA,
					CONSTANT,
					DIFFERENT,
					DIVIDE,
					END,
					EQUAL,
					GREATER_EQUAL,
					GREATER_THAN,
					LOWER_EQUAL,
					LOWER_THAN,
					MODULO,
					MULTIPLY,
					MINUS,
					NOT,
					NUMBER,
					PARENTHESIS_BEGIN,
					PARENTHESIS_END,
					PIPE,
					PLUS,
					REFERENCE,
					STRING,
					UNKNOWN
				};

				Lexer (const char*);

				const std::string&	getCurrent () const;
				Glay::Int32u		getIndex () const;
				Lexem				getType () const;

				bool	next ();

			private:
				bool	read ();

				char						character;
				std::string					current;
				bool						eof;
				Glay::Int32u				index;
				Glay::Pipe::BinaryReader	reader;
				Glay::Pipe::MemoryIStream	stream;
				Lexem						type;
		};
	}
}

#endif

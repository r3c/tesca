
#ifndef __TESCA_EXPRESSION_LEXER_HPP
#define __TESCA_EXPRESSION_LEXER_HPP

#include <sstream>
#include <string>
#include "../../lib/glay/src/glay.hpp"

namespace Tesca
{
	namespace Expression
	{
		class Lexer
		{
			public:
				enum LexemType
				{
					AMPERSAND,
					COMMA,
					DIFFERENT,
					DIVIDE,
					END,
					EQUAL,
					GREATER_EQUAL,
					GREATER_THAN,
					IDENTIFIER,
					LOWER_EQUAL,
					LOWER_THAN,
					MODULO,
					MULTIPLY,
					MINUS,
					NAME,
					NOT,
					NUMBER,
					PARENTHESIS_BEGIN,
					PARENTHESIS_END,
					PIPE,
					PLUS,
					STRING,
					UNKNOWN
				};

				Lexer (const char*);

				Glay::Size getIndex () const;
				const std::string& getLexemText () const;
				LexemType getLexemType () const;

				bool next ();

			private:
				bool read ();

				char character;
				bool eof;
				Glay::Size index;
				std::string lexemText;
				LexemType lexemType;
				Glay::Pipe::BinaryReader reader;
				Glay::Pipe::MemoryIStream stream;
		};
	}
}

#endif

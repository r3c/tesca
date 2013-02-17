
#ifndef __TESCA_EXPRESSION_LEXER_HPP
#define __TESCA_EXPRESSION_LEXER_HPP

#include "../glay/glay.hpp"

namespace	Tesca
{
	class	Lexer
	{
		public:
			Lexer (const char*);

			char			getCurrent () const;
			Glay::Int32u	getIndex () const;

			bool	eof () const;
			bool	next ();

		private:
			char						current;
			bool						finished;
			Glay::Int32u				index;
			Glay::Pipe::TypeReader		reader;
			Glay::Pipe::MemoryIStream	stream;
	};
}

#endif

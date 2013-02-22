
#ifndef __TESCA_STREAM_READER_LINE_HPP
#define __TESCA_STREAM_READER_LINE_HPP

#include "../../glay/glay.hpp"
#include "../reader.hpp"

namespace	Tesca
{
	class	LineReader : public Reader
	{
		public:
			LineReader (const LineReader&);
			LineReader (Glay::Pipe::IStream*);

			LineReader&	operator = (const LineReader&);

			virtual bool	next ();

		protected:
			virtual void	parse (const char*, Glay::Int32u) = 0;
			bool			read (const char**, Glay::Int32u*);

		private:
			char*					buffer;
			bool					eof;
			Glay::Pipe::IStream&	input;
			Glay::Int32u			length;
			Glay::Int32u			size;
			Glay::Int32u			start;
			Glay::Int32u			stop;
	};
}

#endif

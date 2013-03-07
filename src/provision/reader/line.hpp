
#ifndef __TESCA_PROVISION_READER_LINE_HPP
#define __TESCA_PROVISION_READER_LINE_HPP

#include "../../glay/glay.hpp"
#include "../reader.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	LineReader : public Reader
		{
			public:
						LineReader (const LineReader&);
						LineReader (Glay::Pipe::IStream*);
				virtual	~LineReader ();

				LineReader&	operator = (const LineReader&);

				virtual bool	next ();

			protected:
				bool			fetch (const char**, Glay::Int32u*);
				virtual bool	parse (const char*, Glay::Int32u) = 0;

			private:
				bool	read ();

				char*					buffer;
				bool					eof;
				Glay::Pipe::IStream&	input;
				Glay::Int32u			length;
				Glay::Int32u			line;
				Glay::Int32u			size;
				Glay::Int32u			start;
				Glay::Int32u			stop;
		};
	}
}

#endif

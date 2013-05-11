
#ifndef __TESCA_PROVISION_READER_LINE_HPP
#define __TESCA_PROVISION_READER_LINE_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../reader.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	LineReader : public Reader
		{
			public:
				LineReader (const LineReader&);
				LineReader (Glay::Pipe::IStream*, Glay::Int32u);
				virtual	~LineReader ();

				LineReader&	operator = (const LineReader&);

				virtual bool	next ();

			protected:
				virtual bool	parse (const char*, Glay::Int32u) = 0;
				bool			read (const char**, Glay::Int32u*);

			private:
				bool	fetch ();

				Glay::Int32u			available;
				char*					buffer;
				bool					eof;
				Glay::Pipe::IStream&	input;
				Glay::Int32u			line;
				Glay::Int32u			reserve;
				Glay::Int32u			size;
				Glay::Int32u			start;
				Glay::Int32u			stop;
		};
	}
}

#endif

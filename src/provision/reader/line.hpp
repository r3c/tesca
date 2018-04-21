
#ifndef __TESCA_PROVISION_READER_LINE_HPP
#define __TESCA_PROVISION_READER_LINE_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../reader.hpp"

namespace Tesca
{
	namespace Provision
	{
		class LineReader : public Reader
		{
			public:
				LineReader (const LineReader&);
				LineReader (Glay::Pipe::SeekIStream*, Glay::Int32u);
				virtual ~LineReader ();

				LineReader& operator = (const LineReader&);

				virtual bool next ();

			protected:
				virtual bool parse (const char*, Glay::Int32u) = 0;
				bool shift (const char**, Glay::Int32u*);

			private:
				bool fetch ();

				char* buffer;
				Glay::Int32u bufferOffset;
				Glay::Int32u bufferReserve;
				Glay::Int32u bufferSize;
				bool eof;
				Glay::Pipe::SeekIStream& input;
				Glay::Int32u line;
				Glay::Int32u start;
				Glay::Int32u stop;
				Glay::Int32u streamMark;
				Glay::Int32u streamRead;
				Glay::Int32u streamSize;
		};
	}
}

#endif


#ifndef __TESCA_PROVISION_READER_LINE_HPP
#define __TESCA_PROVISION_READER_LINE_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../reader.hpp"

namespace Tesca
{
	namespace Provision
	{
		class LineReader : public Reader
		{
			public:
				LineReader (LineReader const&);
				LineReader (Glay::Pipe::SeekIStream*, Glay::Size);
				virtual ~LineReader ();

				LineReader& operator = (LineReader const&);

				virtual bool next ();

			protected:
				virtual bool parse (const char*, Glay::Size) = 0;
				bool shift (const char**, Glay::Size*);

			private:
				bool fetch ();

				char* buffer;
				Glay::Size bufferOffset;
				Glay::Size bufferReserve;
				Glay::Size bufferSize;
				bool eof;
				Glay::Pipe::SeekIStream& input;
				Glay::Size line;
				Glay::Size start;
				Glay::Size stop;
				Glay::Size streamMark;
				Glay::Size streamRead;
				Glay::Size streamSize;
		};
	}
}

#endif

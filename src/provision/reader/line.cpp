
#include "line.hpp"

#include <cstring>
#include <sstream>

using namespace std;
using namespace Glay;

namespace
{
	const Int32u READ_UPDATE = 1024 * 1024;
}

namespace Tesca
{
	namespace Provision
	{
		LineReader::LineReader (Pipe::SeekIStream* input, Int32u reserve) :
			buffer (0),
			bufferOffset (0),
			bufferReserve (reserve),
			bufferSize (0),
			eof (false),
			input (*input),
			line (0),
			start (0),
			stop (0)
		{
			this->streamMark = 0;
			this->streamRead = 0;
			this->streamSize = input->getSize ();
		}

		LineReader::~LineReader ()
		{
			if (this->buffer)
				free (this->buffer);
		}

		bool LineReader::next ()
		{
			const char* buffer;
			Int32u length;

			if (!this->shift (&buffer, &length))
				return false;

			if (!this->parse (buffer, length))
			{
				stringstream stream;

				stream << "could not parse invalid line #" << this->line;

				this->error.fire (stream.str ());
			}

			return true;
		}

		bool LineReader::fetch ()
		{
			Int32u count;
			char* swap;

			// Nothing to fetch if eof of file has already been reached last time
			if (this->eof)
				return false;

			// Make some buffer space by moving unused content or resizing it
			if (this->start > 0)
			{
				count = this->start;

				memmove (this->buffer, this->buffer + count, sizeof (*this->buffer) * (this->bufferOffset - count));

				this->bufferOffset -= count;
				this->start = 0;
				this->stop -= count;
			}
			else
			{
				this->bufferSize = max (this->bufferSize * 2 + 1, this->bufferReserve);

				swap = static_cast<char*> (realloc (this->buffer, sizeof (*this->buffer) * this->bufferSize));

				if (swap == 0)
				{
					if (this->buffer)
						free (this->buffer);

					this->buffer = 0;
					this->bufferSize = 0;

					return false;
				}

				this->buffer = swap;
			}

			// Read data from stream to buffer
			count = this->input.read (this->buffer + this->bufferOffset, this->bufferSize - this->bufferOffset);

			if (count < this->bufferSize - this->bufferOffset)
				this->eof = true;

			this->bufferOffset += count;
			this->streamRead += count;

			// Send progress event
			if (this->streamMark + READ_UPDATE < this->streamRead || this->streamRead == this->streamSize)
			{
				this->read.fire (Progress (this->streamRead, this->streamSize));
				this->streamMark = this->streamRead;
			}

			return true;
		}

		bool LineReader::shift (const char** line, Int32u* length)
		{
			const char* head;
			const char* tail;

			// Capture characters until next line break
			while (true)
			{
				head = this->buffer + this->stop;
				tail = this->buffer + this->bufferOffset;

				while (head < tail && *head != '\n' && *head != '\r')
					++head;

				this->stop = head - this->buffer;

				if (this->stop < this->bufferOffset || this->eof)
					break;

				if (!this->fetch ())
					return false;
			}

			// Store captured string length
			*length = this->stop - this->start;

			++this->line;

			// Ignore repeated line break characters
			if (this->stop < this->bufferOffset)
			{
				++this->stop;

				if (this->stop < this->bufferOffset || (this->fetch () && this->stop < this->bufferOffset))
				{
					head = this->buffer + this->stop - 1;
					tail = head + 1;

					if ((*tail == '\n' || *tail == '\r') && *head != *tail)
						++this->stop;
				}
			}

			// Store captured string start
			*line = this->buffer + this->start;

			if (this->start == this->stop && this->eof)
				return false;

			this->start = this->stop;

			return true;
		}
	}
}

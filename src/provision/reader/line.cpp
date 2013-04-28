
#include "line.hpp"

#include <sstream>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	namespace	Provision
	{
		LineReader::LineReader (Pipe::IStream* input, Int32u reserve) :
			available (0),
			buffer (0),
			eof (false),
			input (*input),
			line (0),
			reserve (reserve),
			size (0),
			start (0),
			stop (0)
		{
		}

		LineReader::~LineReader ()
		{
			if (this->buffer)
				free (this->buffer);
		}

		bool	LineReader::next ()
		{
			const char*	buffer;
			Int32u		length;

			if (!this->read (&buffer, &length))
				return false;

			if (!this->parse (buffer, length))
			{
				stringstream	stream;

				stream << "could not parse invalid line #" << this->line;

				this->error.fire (stream.str ());
			}

			return true;
		}

		bool	LineReader::fetch ()
		{
			Int32u	count;
			char*	swap;

			// Nothing to fetch if eof of file has already been reached last time
			if (this->eof)
				return false;

			// Make some buffer space by moving unused content or resizing it
			if (this->start > 0)
			{
				count = this->start;

				memmove (this->buffer, this->buffer + count, sizeof (*this->buffer) * (this->available - count));

				this->available -= count;
				this->start = 0;
				this->stop -= count;
			}
			else
			{
				this->size = max (this->size * 2 + 1, this->reserve);

				swap = static_cast<char*> (realloc (this->buffer, sizeof (*this->buffer) * this->size));

				if (swap == 0)
				{
					if (this->buffer)
						free (this->buffer);

					this->buffer = 0;
					this->size = 0;

					return false;
				}

				this->buffer = swap;
			}

			// Read data from stream to buffer
			count = this->input.read (this->buffer + this->available, this->size - this->available);

			if (count < this->size - this->available)
				this->eof = true;

			this->available += count;

			return true;
		}

		bool	LineReader::read (const char** line, Int32u* length)
		{
			const char*	head;
			const char*	tail;

			// Capture characters until next line break
			while (true)
			{
				head = this->buffer + this->stop;
				tail = this->buffer + this->available;

				while (head < tail && *head != '\n' && *head != '\r')
					++head;

				this->stop = head - this->buffer;

				if (this->stop < this->available || this->eof)
					break;

				if (!this->fetch ())
					return false;
			}

			// Store captured string length
			*length = this->stop - this->start;

			++this->line;

			// Ignore repeated line break characters
			if (this->stop < this->available)
			{
				++this->stop;

				if (this->stop < this->available || (this->fetch () && this->stop < this->available))
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

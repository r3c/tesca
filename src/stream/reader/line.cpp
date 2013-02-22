
#include "line.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	LineReader::LineReader (Pipe::IStream* input) :
		buffer (0),
		eof (false),
		input (*input),
		length (0),
		size (0),
		start (0),
		stop (0)
	{
	}

	bool	LineReader::next ()
	{
		const char*	buffer;
		Int32u		length;

		if (!this->read (&buffer, &length))
			return false;

		this->parse (buffer, length);

		return true;
	}

	bool	LineReader::read (const char** buffer, Int32u* length)
	{
		bool	capture;
		Int32u	count;
		Int32u	marker;
		char*	swap;

		// Read next line from stream
		capture = true;

		while (true)
		{
			// Capture characters until next line break then ignore line breaks
			if (capture)
			{
				while (this->stop < this->length && (this->buffer[this->stop] != '\n' && this->buffer[this->stop] != '\r'))
					++this->stop;

				if (this->start == this->stop && this->eof)
					return false;

				if (this->stop < this->length || this->eof)
				{
					capture = false;
					marker = this->stop;
				}
			}
			else
			{
				while (this->stop < this->length && (this->buffer[this->stop] == '\n' || this->buffer[this->stop] == '\r'))
					++this->stop;

				if (this->stop < this->length || this->eof)
					break;
			}

			// Make some buffer space by moving unused content or resizing it
			if (this->start > 0)
			{
				count = this->start;

				memmove (this->buffer, this->buffer + count, sizeof (*this->buffer) * (this->length - count));

				this->length -= count;
				this->start = 0;
				this->stop -= count;

				marker -= count;
			}
			else
			{
				this->size = this->size * 2 + 1;

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
			count = this->input.read (this->buffer + this->length, this->size - this->length);

			if (count < this->size - this->length)
				this->eof = true;

			this->length += count;
		}

		// Set capture information and exit
		*buffer = this->buffer + this->start;
		*length = marker - this->start;

		this->start = this->stop;

		return true;
	}
}

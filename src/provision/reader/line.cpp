
#include "line.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	namespace	Provision
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

		LineReader::~LineReader ()
		{
			if (this->buffer)
				free (this->buffer);
		}

		bool	LineReader::fetch (const char** buffer, Int32u* length)
		{
			// Capture characters until next line break
			while (true)
			{
				while (this->stop < this->length && (this->buffer[this->stop] != '\n' && this->buffer[this->stop] != '\r'))
					++this->stop;

				if (this->start == this->stop && this->eof)
					return false;

				if (this->stop < this->length || this->eof)
					break;

				if (!this->read ())
					return false;
			}

			// Store captured string length
			*length = this->stop - this->start;

			// Ignore repeated line break characters
			while (true)
			{
				while (this->stop < this->length && (this->buffer[this->stop] == '\n' || this->buffer[this->stop] == '\r'))
					++this->stop;

				if (this->stop < this->length || this->eof)
					break;

				if (!this->read ())
					return false;
			}

			// Store captured string start
			*buffer = this->buffer + this->start;

			this->start = this->stop;

			return true;
		}

		bool	LineReader::next ()
		{
			const char*	buffer;
			Int32u		length;

			if (!this->fetch (&buffer, &length))
				return false;

			if (!this->parse (buffer, length))
				++this->errors;

			return true;
		}

		bool	LineReader::read ()
		{
			Int32u	count;
			char*	swap;

			// Make some buffer space by moving unused content or resizing it
			if (this->start > 0)
			{
				count = this->start;

				memmove (this->buffer, this->buffer + count, sizeof (*this->buffer) * (this->length - count));

				this->length -= count;
				this->start = 0;
				this->stop -= count;
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

			return true;
		}
	}
}

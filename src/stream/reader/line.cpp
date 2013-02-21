
#include "line.hpp"

using namespace std;
using namespace Glay;

#warning FIXME
#include <iostream>

namespace	Tesca
{
	LineReader::LineReader (Pipe::IStream* input) :
		buffer (0),
		capture (true),
		cursor (0),
		eof (false),
		input (*input),
		size (0),
		store (0)
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
		Int32u	delta;
		char*	swap;

		// Move unused data at the beginning of buffer
		delta = this->store - this->cursor;

		memmove (this->buffer, this->buffer + this->cursor, delta);
cout << "remaining = " << delta << ": [" << string (this->buffer, delta) << "]" << endl;
		this->cursor = delta;
		this->store = delta;

		// Append incoming data from string into buffer
		Int32u	i = 0;

		while (true)
		{
			delta = this->input.read (this->buffer + this->cursor, this->size - this->store);
cout << "read " << delta << " bytes on " << (this->size - this->store) << ": [" << string (this->buffer + this->cursor, delta) << "]" << endl;
			if (delta < this->size - this->store)
				this->eof = true;

			this->store += delta;

			if (this->capture)
			{
				while (i < this->store && (this->buffer[i] != '\n' && this->buffer[i] != '\r'))
					++i;

				this->cursor = i;

				if (i < this->store || this->eof)
				{
					this->capture = false;

					*buffer = this->buffer;
					*length = i;

					return i > 0;
				}
			}
			else
			{
				while (i < this->store && (this->buffer[i] == '\n' || this->buffer[i] == '\r'))
					++i;

				this->cursor = i;

				if (i < this->store || this->eof)
				{
					this->capture = true;

					this->cursor = 0;
					this->store -= i;

					memmove (this->buffer, this->buffer + i, this->store);

					continue;
				}
			}

			this->size = this->size * 2 + 1;

			swap = static_cast<char*> (realloc (this->buffer, sizeof (*this->buffer) * this->size));

			if (swap == 0)
			{
				free (this->buffer);

				this->buffer = 0;
				this->size = 0;

				return false;
			}

			this->buffer = swap;
		}
	}
}

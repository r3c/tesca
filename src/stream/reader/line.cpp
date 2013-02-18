
#include "line.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	LineReader::LineReader (Pipe::IStream* input) :
		input (*input)
	{
		this->set = this->input.read (&this->current, sizeof (this->current)) == sizeof (this->current);
	}

	bool	LineReader::next ()
	{
		stringstream	buffer;

		if (!this->read (buffer))
			return false;

		this->parse (buffer.str ());

		return true;
	}

	bool	LineReader::read (stringstream& buffer)
	{
		if (!this->set)
			return false;

		while (this->current != '\n' && this->current != '\r')
		{
			buffer << this->current;

			if (this->input.read (&this->current, sizeof (this->current)) != sizeof (this->current))
			{
				this->set = false;

				return true;
			}
		}

		while (this->current == '\n' || this->current == '\r')
		{
			if (this->input.read (&this->current, sizeof (this->current)) != sizeof (this->current))
			{
				this->set = false;

				return true;
			}
		}

		return true;
	}
}

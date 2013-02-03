
#include "lexer.hpp"

using namespace Glay;

namespace	Tesca
{
	Lexer::Lexer (const char* input) :
		current (0),
		finished (false),
		index (0),
		reader (stream),
		stream (input, strlen (input))
	{
		this->next ();
	}

	char	Lexer::getCurrent () const
	{
		return this->current;
	}

	Int32u	Lexer::getIndex () const
	{
		return this->index;
	}

	bool	Lexer::eof () const
	{
		return this->finished;
	}

	bool	Lexer::next ()
	{
		if (reader.read (&this->current))
		{
			++this->index;

			return true;
		}

		this->current = -1;
		this->finished = true;

		return false;
	}
}

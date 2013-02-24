
#include "format.hpp"

#include <cstring>

using namespace Glay;

namespace	Tesca
{
	Format::Format () :
		parser (0)
	{
	
	}

	Format::~Format ()
	{
	}

	Reader*	Format::create (Pipe::IStream* stream, const Reader::Fields* fields) const
	{
		if (this->parser != 0)
			return this->parser->builder (stream, fields, this->config.c_str ());

		return 0;
	}

	bool	Format::parse (const char* expression)
	{
		const char*	stop;

		for (stop = expression; *stop != '\0' && *stop != ':'; )
			++stop;

		for (Int32u i = 0; Parser::parsers[i].name; ++i)
		{
			if (strncmp (Parser::parsers[i].name, expression, stop - expression) == 0)
			{
				this->parser = &Parser::parsers[i];

				break;
			}
		}

		if (*stop != '\0')
			this->config = stop + 1;
		else
			this->config = "";

		return this->parser != 0;
	}
}

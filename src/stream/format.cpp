
#include "format.hpp"

#include <cstring>

using namespace Glay;

namespace	Tesca
{
	Format::Format ()
	{
	}

	Format::~Format ()
	{
	}

	Reader*	Format::create (Pipe::IStream* stream, const Reader::Fields* fields, const char* expression) const
	{
		const Parser*	parser;
		const char*		stop;

		for (stop = expression; *stop != '\0' && *stop != ':'; )
			++stop;

		parser = 0;

		for (Int32u i = 0; Parser::parsers[i].name; ++i)
		{
			if (strncmp (Parser::parsers[i].name, expression, stop - expression) == 0)
			{
				parser = &Parser::parsers[i];

				break;
			}
		}

		if (!parser)
			return 0;

		if (*stop != '\0')
			++stop;

		return parser->builder (stream, fields, stop);
	}
}


#include "format.hpp"

#include <cstring>
#include <sstream>

using namespace std;
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
			return this->parser->builder (stream, fields, this->config);

		return 0;
	}

	bool	Format::parse (const char* expression)
	{
		stringstream	buffer;
		string			key;
		const char*		stop;

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

		// Read configuration
		this->config.clear ();

		while (*stop != '\0')
		{
			// Read configuration key
			buffer.str ("");

			for (++stop; *stop != '\0' && *stop != '='; ++stop)
			{
				if (*stop == '\\' && *(stop + 1) != '\0')
					++stop;

				buffer.put (*stop);
			}

			if (*stop == '\0')
				break;

			key = buffer.str ();

			// Read and store configuration pair
			buffer.str ("");

			for (++stop; *stop != '\0' && *stop != ';'; ++stop)
			{
				if (*stop == '\\' && *(stop + 1) != '\0')
					++stop;

				buffer.put (*stop);
			}

			this->config[key] = buffer.str ();
		}

		return this->parser != 0;
	}
}

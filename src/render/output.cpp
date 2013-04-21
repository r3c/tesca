
#include "output.hpp"

#include <cstring>
#include <sstream>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	namespace	Render
	{
		Output::Output () :
			format (0)
		{
		}

		Output::~Output ()
		{
		}

		const Output::Error&	Output::getError () const
		{
			return this->error;
		}

		Output::Error&	Output::getError ()
		{
			return this->error;
		}

		Printer*	Output::create () const
		{
			if (this->format != 0)
				return this->format->builder (/*this->config*/);

			return 0;
		}

		bool	Output::parse (const char* expression)
		{
			stringstream	buffer;
			string			key;
			const char*		stop;

			for (stop = expression; *stop != '\0' && *stop != ':'; )
				++stop;

			this->format = 0;

			for (auto current = Format::formats; current->name; ++current)
			{
				if (strncmp (current->name, expression, stop - expression) == 0)
				{
					this->format = current;

					break;
				}
			}

			if (!this->format)
			{
				this->error.fire (string ("unknown format \"") + string (expression, stop - expression) + "\"");

				return false;
			}

			// Read configuration
/*
			this->config.clear ();

			while (*stop != '\0')
			{
				// Read configuration key
				buffer.str ("");

				for (++stop; *stop != '\0' && *stop != '=' && *stop != ';'; ++stop)
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

				if (*stop == '=')
				{
					for (++stop; *stop != '\0' && *stop != ';'; ++stop)
					{
						if (*stop == '\\' && *(stop + 1) != '\0')
							++stop;

						buffer.put (*stop);
					}
				}

				this->config.set (key, buffer.str ());
			}
*/
			return true;
		}
	}
}


#include "output.hpp"

#include <cstring>

using namespace std;
using namespace Glay;

namespace
{
	static const Int8u SEPARATOR = ':';
}

namespace Tesca
{
	namespace Render
	{
		Output::Output () :
			format (0)
		{
		}

		Output::~Output ()
		{
		}

		const Output::Error& Output::onError () const
		{
			return this->error;
		}

		Output::Error& Output::onError ()
		{
			return this->error;
		}

		Printer* Output::create () const
		{
			if (this->format != 0)
				return this->format->builder (this->config);

			return 0;
		}

		bool Output::parse (const char* expression)
		{
			const char* begin;
			string key;

			for (begin = expression; *expression != '\0' && *expression != SEPARATOR; )
				++expression;

			this->format = 0;

			for (auto current = Format::formats; current->name; ++current)
			{
				if (strncmp (current->name, begin, expression - begin) == 0)
				{
					this->format = current;

					break;
				}
			}

			if (!this->format)
			{
				this->error.fire (string ("unknown format \"") + string (begin, expression - begin) + "\"");

				return false;
			}

			// Read configuration
			if (*expression == SEPARATOR)
				return this->config.parse (++expression);

			return true;
		}
	}
}

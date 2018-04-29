
#include "input.hpp"

#include <cstring>

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;

namespace
{
	static const Int8u SEPARATOR = ':';
}

namespace Tesca
{
	namespace Provision
	{
		Input::Input () :
			format (0)
		{
		}

		Input::~Input ()
		{
		}

		const Input::Error& Input::onError () const
		{
			return this->error;
		}

		Input::Error& Input::onError ()
		{
			return this->error;
		}

		Reader* Input::create (SeekIStream* stream, const Lookup& lookup) const
		{
			if (this->format != 0)
				return this->format->builder (stream, lookup, this->config);

			return 0;
		}

		bool Input::parse (const char* expression)
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

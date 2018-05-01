
#include "config.hpp"

#include <sstream>
#include "../../lib/glay/src/glay.hpp"

using namespace std;
using namespace Glay;

namespace
{
	static Int8u const ESCAPE = '\\';
	static Int8u const PARAMETER = ':';
	static Int8u const VALUE = '=';
}

namespace Tesca
{
	namespace Storage
	{
		Config::Config ()
		{
		}

		void Config::clear ()
		{
			this->values.clear ();
		}

		const string& Config::get (const string& key, const string& fallback) const
		{
			auto i = this->values.find (key);

			if (i == this->values.end ())
				return fallback;

			return i->second;
		}

		bool Config::get (const string& key, string* value) const
		{
			auto i = this->values.find (key);

			if (i == this->values.end ())
				return false;

			if (value)
				*value = i->second;

			return true;
		}

		bool Config::parse (const char* input)
		{
			stringstream buffer;
			string key;

			this->clear ();

			for (const char* c = input; *c != '\0'; )
			{
				// Read configuration key
				buffer.str ("");

				for (; *c != '\0' && *c != PARAMETER && *c != VALUE; ++c)
				{
					if (*c == ESCAPE && *(c + 1) != '\0')
						++c;

					buffer.put (*c);
				}

				key = buffer.str ();

				// Read configuration value if any
				buffer.str ("");

				if (*c == VALUE)
				{
					for (++c; *c != '\0' && *c != PARAMETER; ++c)
					{
						if (*c == ESCAPE && *(c + 1) != '\0')
							++c;

						buffer.put (*c);
					}
				}

				// Skip parameter separator
				if (*c == PARAMETER)
					++c;

				// Store configuration pair
				this->values[key] = buffer.str ();
			}

			return true;
		}
	}
}

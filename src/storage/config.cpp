
#include "config.hpp"

#include <sstream>

using namespace std;

namespace	Tesca
{
	namespace	Storage
	{
		Config::Config ()
		{
		}

		void	Config::clear ()
		{
			this->values.clear ();
		}

		const string&	Config::get (const string& key, const string& fallback) const
		{
			auto	i = this->values.find (key);

			if (i == this->values.end ())
				return fallback;

			return i->second;
		}

		bool	Config::get (const string& key, string* value) const
		{
			auto	i = this->values.find (key);

			if (i == this->values.end ())
				return false;

			if (value)
				*value = i->second;

			return true;
		}

		bool	Config::parse (const string& input)
		{
			stringstream	buffer;
			string			key;

			this->clear ();

			for (const char* c = input.c_str (); *c != '\0'; )
			{
				// Read configuration key
				buffer.str ("");

				for (; *c != '\0' && *c != '=' && *c != ';'; ++c)
				{
					if (*c == '\\' && *(c + 1) != '\0')
						++c;

					buffer.put (*c);
				}

				key = buffer.str ();

				// Read and store configuration pair
				buffer.str ("");

				if (*c == '=')
				{
					for (++c; *c != '\0' && *c != ';'; ++c)
					{
						if (*c == '\\' && *(c + 1) != '\0')
							++c;

						buffer.put (*c);
					}
				}

				// Skip separator
				if (*c == ';')
					++c;

				this->values[key] = buffer.str ();
			}

			return true;
		}
	}
}


#include "config.hpp"

using namespace std;

namespace	Tesca
{
	namespace	Provision
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

			*value = i->second;

			return true;
		}

		void	Config::set (const string& key, const string& value)
		{
			this->values[key] = value;
		}
	}
}

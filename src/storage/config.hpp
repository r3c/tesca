
#ifndef __TESCA_STORAGE_CONFIG_HPP
#define __TESCA_STORAGE_CONFIG_HPP

#include <map>
#include <string>

namespace Tesca
{
	namespace Storage
	{
		class Config
		{
			public:
				Config (Config const&);
				Config ();

				Config& operator = (Config const&);

				void clear ();
				const std::string& get (const std::string&, const std::string&) const;
				bool get (const std::string&, std::string*) const;
				bool parse (const char*);

			private:
				std::map<std::string, std::string> values;
		};
	}
}

#endif

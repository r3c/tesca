
#ifndef __TESCA_PROVISION_READER_MAP_HPP
#define __TESCA_PROVISION_READER_MAP_HPP

#include <list>
#include <map>
#include <string>
#include "../row/array.hpp"
#include "../reader.hpp"

namespace Tesca
{
	namespace Provision
	{
		class MapReader : public Reader
		{
			public:
				typedef std::map<std::string, Glay::Int32u> Fields;

				MapReader (MapReader const&);
				MapReader (Fields const*);
				virtual ~MapReader ();

				MapReader& operator = (MapReader const&);

				bool assign (const std::string&, Storage::Variant const&);
				virtual Row const& current () const;
				virtual bool next ();
				void push ();

			private:
				typedef std::list<Storage::Variant*> Lines;

				Fields const* fields;
				Lines lines;
				ArrayRow row;
		};
	}
}

#endif

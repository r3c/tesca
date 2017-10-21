
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

				MapReader (const MapReader&);
				MapReader (const Fields*);
				virtual ~MapReader ();

				MapReader& operator = (const MapReader&);

				bool assign (const std::string&, const Storage::Variant&);
				virtual const Row& current () const;
				virtual bool next ();
				void push ();

			private:
				typedef std::list<Storage::Variant*> Lines;

				const Fields* fields;
				Lines lines;
				ArrayRow row;
		};
	}
}

#endif

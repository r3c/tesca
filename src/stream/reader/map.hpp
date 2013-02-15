
#ifndef __TESCA_READER_MAP_HPP
#define __TESCA_READER_MAP_HPP

#include <list>
#include <utility>
#include <vector>
#include "../reader.hpp"
#include "../variant.hpp"

namespace	Tesca
{
	class	MapReader : public Reader
	{
		public:
			/**/				MapReader (const MapReader&);
			/**/				MapReader ();

			MapReader&			operator = (const MapReader&);

			virtual const Row&	current () const;
			virtual bool		next ();
			void				push ();
			bool				set (const std::string&, const Variant&);

		private:
			typedef std::vector<std::pair<std::string, Variant>>	Fields;
			typedef std::list<Fields>								Lines;

			Lines	lines;
			Row		row;
	};
}

#endif

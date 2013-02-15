
#ifndef __TESCA_COLUMN_HPP
#define __TESCA_COLUMN_HPP

#include <string>
#include "../stream/row.hpp"
#include "../stream/variant.hpp"
#include "accessor.hpp"
#include "slot.hpp"

namespace	Tesca
{
	class	Column
	{
		public:
			/**/	Column (const Column&);
			/**/	Column (const std::string&, const Accessor*);

			Column&	operator = (const Column&);

			const std::string&	getIdentifier () const;

			virtual Slot*		create () const = 0;
			virtual bool		key () const = 0;
			Variant				read (const Row&) const;

		private:
			const Accessor*	accessor;
			std::string		identifier;
	};
}

#endif


#ifndef __TESCA_COLUMN_HPP
#define __TESCA_COLUMN_HPP

#include "row.hpp"
#include "slot.hpp"
#include "value.hpp"

namespace	Tesca
{
	class Column
	{
		public:
			/**/					Column (const Column&);
			/**/					Column ();
			virtual					~Column ();

			Column&					operator = (const Column&);

			virtual Slot*			create () const = 0;
			virtual const Value&	key () const = 0;
			virtual void			update (const Row&) = 0;
			virtual const Value&	value () const = 0;
	};
}

#endif

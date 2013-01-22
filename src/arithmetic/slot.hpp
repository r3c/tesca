
#ifndef __TESCA_SLOT_HPP
#define __TESCA_SLOT_HPP

#include "value.hpp"

namespace	Tesca
{
	class	Slot
	{
		public:
			/**/					Slot (const Slot&);
			/**/					Slot ();
			virtual					~Slot ();

			Slot&					operator = (const Slot&);

			virtual void			append (const Value&) = 0;
			virtual const Value&	value () const = 0;
	};
}

#endif

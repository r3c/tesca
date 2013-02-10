
#ifndef __TESCA_SLOT_HPP
#define __TESCA_SLOT_HPP

#include "variant.hpp"

namespace	Tesca
{
	class	Slot
	{
		public:
			/**/			Slot (const Slot&);
			/**/			Slot ();

			Slot&			operator = (const Slot&);

			virtual Variant	current () const = 0;
			virtual bool	push (const Variant&) = 0;
			virtual void	reset () = 0;
	};
}

#endif

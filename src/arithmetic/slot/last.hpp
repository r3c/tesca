
#ifndef __TESCA_SLOT_LAST_HPP
#define __TESCA_SLOT_LAST_HPP

#include "../../glay/glay.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	class	LastSlot : public Slot
	{
		public:
			virtual Variant	current () const;
			virtual bool	push (const Variant&);
			virtual void	reset ();

		private:
			Variant	last;
	};
}

#endif

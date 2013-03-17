
#ifndef __TESCA_SLOT_LAST_HPP
#define __TESCA_SLOT_LAST_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	class	LastSlot : public Slot
	{
		public:
			virtual Provision::Variant	current () const;
			virtual bool			push (const Provision::Variant&);
			virtual void			reset ();

		private:
			Provision::Variant	last;
	};
}

#endif

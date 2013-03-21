
#ifndef __TESCA_SLOT_COUNT_HPP
#define __TESCA_SLOT_COUNT_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	class	CountSlot : public Slot
	{
		public:
			CountSlot ();

			virtual Provision::Variant	current () const;
			virtual bool			push (const Provision::Variant&);
			virtual void			reset ();

		private:
			Glay::Int32u	count;
	};
}

#endif

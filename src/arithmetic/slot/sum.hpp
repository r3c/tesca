
#ifndef __TESCA_SLOT_SUM_HPP
#define __TESCA_SLOT_SUM_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	class	SumSlot : public Slot
	{
		public:
			SumSlot ();

			virtual Provision::Variant	current () const;
			virtual bool			push (const Provision::Variant&);
			virtual void			reset ();

		private:
			Glay::Float64	sum;
	};
}

#endif

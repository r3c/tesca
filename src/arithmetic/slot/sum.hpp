
#ifndef __TESCA_SLOT_SUM_HPP
#define __TESCA_SLOT_SUM_HPP

#include "../../glay/glay.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	class	SumSlot : public Slot
	{
		public:
			SumSlot ();

			virtual Stream::Variant	current () const;
			virtual bool			push (const Stream::Variant&);
			virtual void			reset ();

		private:
			Glay::Float64	sum;
	};
}

#endif

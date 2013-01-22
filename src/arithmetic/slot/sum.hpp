
#ifndef __TESCA_SLOT_SUM_HPP
#define __TESCA_SLOT_SUM_HPP

#include "../../glay/glay.hpp"
#include "../value/number.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	class	SumSlot : public Slot
	{
		public:
			/**/					SumSlot ();

			virtual void			append (const Value&);
			virtual const Value&	value () const;

		private:
			mutable NumberValue	result;
			Glay::Float64		sum;
	};
}

#endif

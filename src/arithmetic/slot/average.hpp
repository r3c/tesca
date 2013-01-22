
#ifndef __TESCA_SLOT_AVERAGE_HPP
#define __TESCA_SLOT_AVERAGE_HPP

#include "../../glay/glay.hpp"
#include "../value/number.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	class	AverageSlot : public Slot
	{
		public:
			/**/					AverageSlot ();

			virtual void			append (const Value&);
			virtual const Value&	value () const;

		private:
			mutable NumberValue		average;
			Glay::Int32u			count;
			Glay::Float64			sum;
	};
}

#endif


#ifndef __TESCA_SLOT_SUM_HPP
#define __TESCA_SLOT_SUM_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	SumSlot : public Slot
		{
			public:
				SumSlot ();

				virtual Storage::Variant	current () const;
				virtual bool				push (const Storage::Variant&);
				virtual void				reset ();

			private:
				Glay::Float64	sum;
		};
	}
}

#endif

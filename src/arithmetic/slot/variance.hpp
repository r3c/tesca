
#ifndef __TESCA_SLOT_VARIANCE_HPP
#define __TESCA_SLOT_VARIANCE_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	VarianceSlot : public Slot
		{
			public:
				VarianceSlot ();

				virtual Storage::Variant	current () const;
				virtual bool				push (const Storage::Variant&);
				virtual void				reset ();

			private:
				Glay::Int32u	count;
				Glay::Float64	mean;
				Glay::Float64	sum;
		};
	}
}

#endif

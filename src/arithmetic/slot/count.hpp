
#ifndef __TESCA_SLOT_COUNT_HPP
#define __TESCA_SLOT_COUNT_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	CountSlot : public Slot
		{
			public:
				CountSlot ();

				virtual Storage::Variant	current () const;
				virtual bool				push (const Storage::Variant&);
				virtual void				reset ();

			private:
				Glay::Int32u	count;
		};
	}
}

#endif

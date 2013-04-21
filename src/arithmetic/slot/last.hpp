
#ifndef __TESCA_SLOT_LAST_HPP
#define __TESCA_SLOT_LAST_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	LastSlot : public Slot
		{
			public:
				virtual Storage::Variant	current () const;
				virtual bool				push (const Storage::Variant&);
				virtual void				reset ();

			private:
				Storage::Variant	last;
		};
	}
}

#endif

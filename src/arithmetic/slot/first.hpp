
#ifndef __TESCA_SLOT_FIRST_HPP
#define __TESCA_SLOT_FIRST_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	FirstSlot : public Slot
		{
			public:
				FirstSlot ();

				virtual Storage::Variant	current () const;
				virtual bool				push (const Storage::Variant&);
				virtual void				reset ();

			private:
				bool				empty;
				Storage::Variant	first;
		};
	}
}

#endif

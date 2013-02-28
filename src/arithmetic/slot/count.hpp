
#ifndef __TESCA_SLOT_COUNT_HPP
#define __TESCA_SLOT_COUNT_HPP

#include "../../glay/glay.hpp"
#include "../slot.hpp"

namespace	Tesca
{
	class	CountSlot : public Slot
	{
		public:
			CountSlot ();

			virtual Stream::Variant	current () const;
			virtual bool			push (const Stream::Variant&);
			virtual void			reset ();

		private:
			Glay::Int32u	count;
	};
}

#endif

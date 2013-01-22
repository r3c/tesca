
#ifndef __TESCA_SLOT_LAST_HPP
#define __TESCA_SLOT_LAST_HPP

#include "../slot.hpp"

namespace	Tesca
{
	class	LastSlot : public Slot
	{
		public:
			/**/					LastSlot ();
			/**/					~LastSlot ();

			virtual void			append (const Value&);
			virtual const Value&	value () const;

		private:
			const Value*	last;
	};
}

#endif

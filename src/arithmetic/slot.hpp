
#ifndef __TESCA_ARITHMETIC_SLOT_HPP
#define __TESCA_ARITHMETIC_SLOT_HPP

#include "../stream/variant.hpp"

namespace	Tesca
{
	class	Slot
	{
		public:
					Slot (const Slot&);
					Slot ();
			virtual	~Slot ();

			Slot&	operator = (const Slot&);

			virtual Stream::Variant	current () const = 0;
			virtual bool			push (const Stream::Variant&) = 0;
			virtual void			reset () = 0;
	};
}

#endif

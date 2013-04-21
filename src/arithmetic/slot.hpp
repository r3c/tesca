
#ifndef __TESCA_ARITHMETIC_SLOT_HPP
#define __TESCA_ARITHMETIC_SLOT_HPP

#include "../storage/variant.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	Slot
		{
			public:
						Slot (const Slot&);
						Slot ();
				virtual	~Slot ();

				Slot&	operator = (const Slot&);

				virtual Storage::Variant	current () const = 0;
				virtual bool				push (const Storage::Variant&) = 0;
				virtual void				reset () = 0;
		};
	}
}

#endif

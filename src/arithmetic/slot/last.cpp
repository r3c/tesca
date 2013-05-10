
#include "last.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		LastSlot::LastSlot () :
			last ()
		{
		}

		Variant	LastSlot::current () const
		{
			return this->last;
		}

		bool	LastSlot::push (const Variant& value)
		{
			this->last = value;
			this->last.keep ();

			return true;
		}

		void	LastSlot::reset ()
		{
			this->last = Variant::empty;
		}
	}
}

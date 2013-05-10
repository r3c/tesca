
#include "first.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		FirstSlot::FirstSlot () :
			empty (true),
			first ()
		{
		}

		Variant	FirstSlot::current () const
		{
			return this->first;
		}

		bool	FirstSlot::push (const Variant& value)
		{
			if (this->empty)
			{
				this->empty = false;
				this->first = value;
				this->first.keep ();
			}

			return true;
		}

		void	FirstSlot::reset ()
		{
			this->empty = true;
			this->first = Variant::empty;
		}
	}
}

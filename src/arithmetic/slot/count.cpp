
#include "count.hpp"

using namespace Glay;
using namespace Tesca::Stream;

namespace	Tesca
{
	CountSlot::CountSlot ()
	{
		this->reset ();
	}

	Variant	CountSlot::current () const
	{
		return Variant (this->count);
	}

	bool	CountSlot::push (const Variant&)
	{
		++this->count;

		return true;
	}

	void	CountSlot::reset ()
	{
		this->count = 0;
	}
}

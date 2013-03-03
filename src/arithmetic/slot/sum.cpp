
#include "sum.hpp"

using namespace Glay;
using namespace Tesca::Provision;

namespace	Tesca
{
	SumSlot::SumSlot ()
	{
		this->reset ();
	}

	Variant	SumSlot::current () const
	{
		return Variant (this->sum);
	}

	bool	SumSlot::push (const Variant& value)
	{
		Float64	number;

		if (!value.toNumber (&number))
			return false;

		this->sum += number;

		return true;
	}

	void	SumSlot::reset ()
	{
		this->sum = 0;
	}
}

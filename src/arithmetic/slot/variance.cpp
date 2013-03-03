
#include "variance.hpp"

using namespace Glay;
using namespace Tesca::Provision;

namespace	Tesca
{
	VarianceSlot::VarianceSlot ()
	{
		this->reset ();
	}

	Variant	VarianceSlot::current () const
	{
		if (this->count > 1)
			return Variant (this->sum / (this->count - 1));

		return Variant::empty;
	}

	/*
	** From:
	** http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm
	*/
	bool	VarianceSlot::push (const Variant& value)
	{
		Float64	delta;
		Float64	number;

		if (!value.toNumber (&number))
			return false;

		delta = number - this->mean;

		++this->count;

		this->mean += delta / this->count;
		this->sum += delta * (number - this->mean);

		return true;
	}

	void	VarianceSlot::reset ()
	{
		this->count = 0;
		this->mean = 0;
		this->sum = 0;
	}
}

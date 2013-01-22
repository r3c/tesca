
#include "sum.hpp"

using namespace Glay;

namespace	Tesca
{
	SumSlot::SumSlot () :
		result (0),
		sum (0)
	{
	}

	void	SumSlot::append (const Value& value)
	{
		Float64	number;

		if (value.toNumber (&number))
			this->sum += number;
	}

	const Value&	SumSlot::value () const
	{
		this->result = NumberValue (this->sum);

		return this->result;
	}
}

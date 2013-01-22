
#include "average.hpp"

#include "../value/void.hpp"

using namespace Glay;

namespace	Tesca
{
	AverageSlot::AverageSlot () :
		average (0),
		count (0),
		sum (0)
	{
	}

	void	AverageSlot::append (const Value& value)
	{
		Float64	number;

		if (value.toNumber (&number))
		{
			this->sum += number;

			++this->count;
		}
	}

	const Value&	AverageSlot::value () const
	{
		if (this->count > 0)
		{
			this->average = NumberValue (this->sum / this->count);

			return this->average;
		}

		return VoidValue::instance;
	}
}

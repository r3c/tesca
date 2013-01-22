
#include "aggregate.hpp"

#include "../value/void.hpp"

namespace	Tesca
{
	AggregateColumn::AggregateColumn (Column* source) :
		MapColumn (source)
	{
	}

	const Value&	AggregateColumn::key () const
	{
		return VoidValue::instance;
	}

	const Value&	AggregateColumn::map (const Value& value)
	{
		return value;
	}
}

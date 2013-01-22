
#include "average.hpp"

#include "../slot/average.hpp"

namespace	Tesca
{
	AverageColumn::AverageColumn (Column* source) :
		AggregateColumn (source)
	{
	}

	Slot*	AverageColumn::create () const
	{
		return new AverageSlot ();
	}
}

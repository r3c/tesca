
#include "sum.hpp"

#include "../slot/sum.hpp"

namespace	Tesca
{
	SumColumn::SumColumn (Column* source) :
		AggregateColumn (source)
	{
	}

	Slot*	SumColumn::create () const
	{
		return new SumSlot ();
	}
}

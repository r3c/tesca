
#include "aggregator.hpp"

#include "../arithmetic/accessor.hpp"
#include "../arithmetic/column/group.hpp"
#include "../arithmetic/slot/average.hpp"
#include "../arithmetic/slot/last.hpp"
#include "../arithmetic/slot/sum.hpp"

namespace	Tesca
{
	const Aggregator	Aggregator::aggregators[] =
	{
		{"avg",		[] (const string& identifier, const Accessor* accessor) -> Column*
		{
			return new GroupColumn<AverageSlot> (identifier, accessor);
		}},
		{"last",	[] (const string& identifier, const Accessor* accessor) -> Column*
		{
			return new GroupColumn<LastSlot> (identifier, accessor);
		}},
		{"sum",		[] (const string& identifier, const Accessor* accessor) -> Column*
		{
			return new GroupColumn<SumSlot> (identifier, accessor);
		}},
		{0, 0}
	};
}

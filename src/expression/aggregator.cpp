
#include "aggregator.hpp"

#include "../arithmetic/column/group.hpp"
#include "../arithmetic/reader.hpp"
#include "../arithmetic/slot/average.hpp"
#include "../arithmetic/slot/last.hpp"
#include "../arithmetic/slot/sum.hpp"

namespace	Tesca
{
	const Aggregator	Aggregator::aggregators[] =
	{
		{"avg",		[] (const string& identifier, const Reader* reader) -> Column*
		{
			return new GroupColumn<AverageSlot> (identifier, reader);
		}},
		{"last",	[] (const string& identifier, const Reader* reader) -> Column*
		{
			return new GroupColumn<LastSlot> (identifier, reader);
		}},
		{"sum",		[] (const string& identifier, const Reader* reader) -> Column*
		{
			return new GroupColumn<SumSlot> (identifier, reader);
		}},
		{0, 0}
	};
}

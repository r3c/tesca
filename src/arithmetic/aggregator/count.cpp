
#include "count.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		CountAggregator::CountAggregator () :
			count (0)
		{
		}

		Variant CountAggregator::collect () const
		{
			return Variant (this->count);
		}

		bool CountAggregator::update (Variant const&)
		{
			++this->count;

			return true;
		}
	}
}

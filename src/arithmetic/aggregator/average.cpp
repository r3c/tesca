
#include "average.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		AverageAggregator::AverageAggregator () :
			count (0),
			sum (0)
		{
		}

		Variant AverageAggregator::collect () const
		{
			if (this->count > 0)
				return Variant (this->sum / this->count);

			return Variant::empty;
		}

		bool AverageAggregator::update (Variant const& value)
		{
			Float64 number;

			if (!value.toNumber (&number))
				return false;

			this->sum += number;

			++this->count;

			return true;
		}
	}
}

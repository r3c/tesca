
#include "sum.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		SumAggregator::SumAggregator () :
			sum (0)
		{
		}

		Variant SumAggregator::collect () const
		{
			return Variant (this->sum);
		}

		bool SumAggregator::update (Variant const& value)
		{
			Float64 number;

			if (!value.toNumber (&number))
				return false;

			this->sum += number;

			return true;
		}
	}
}

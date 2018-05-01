
#include "max.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		MaxAggregator::MaxAggregator () :
			empty (true),
			max (0)
		{
		}

		Variant MaxAggregator::collect () const
		{
			if (this->empty)
				return Variant::empty;

			return Variant (this->max);
		}

		bool MaxAggregator::update (Variant const& value)
		{
			Float64 current;

			if (!value.toNumber (&current))
				return false;

			if (this->empty || current > this->max)
			{
				this->empty = false;
				this->max = current;
			}

			return true;
		}
	}
}

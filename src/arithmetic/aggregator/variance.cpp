
#include "variance.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		VarianceAggregator::VarianceAggregator () :
			count (0),
			mean (0),
			sum (0)
		{
		}

		Variant VarianceAggregator::collect () const
		{
			if (this->count > 1)
				return Variant (this->sum / (this->count - 1));

			return Variant::empty;
		}

		/*
		** From:
		** http://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Online_algorithm
		*/
		bool VarianceAggregator::update (Variant const& value)
		{
			Float64 number;

			if (!value.toNumber (&number))
				return false;

			Float64 delta = number - this->mean;

			++this->count;

			this->mean += delta / this->count;
			this->sum += delta * (number - this->mean);

			return true;
		}
	}
}

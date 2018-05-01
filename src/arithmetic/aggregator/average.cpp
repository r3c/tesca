
#include "average.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		AverageAggregator::AverageAggregator ()
		{
			this->reset ();
		}

		Variant AverageAggregator::collect () const
		{
			if (this->count > 0)
				return Variant (this->sum / this->count);

			return Variant::empty;
		}

		void AverageAggregator::reset ()
		{
			this->count = 0;
			this->sum = 0;
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

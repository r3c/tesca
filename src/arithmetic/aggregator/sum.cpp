
#include "sum.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		SumAggregator::SumAggregator ()
		{
			this->reset ();
		}

		Variant SumAggregator::collect () const
		{
			return Variant (this->sum);
		}

		void SumAggregator::reset ()
		{
			this->sum = 0;
		}

		bool SumAggregator::update (const Variant& value)
		{
			Float64 number;

			if (!value.toNumber (&number))
				return false;

			this->sum += number;

			return true;
		}
	}
}

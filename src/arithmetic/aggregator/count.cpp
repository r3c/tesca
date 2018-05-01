
#include "count.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		CountAggregator::CountAggregator ()
		{
			this->reset ();
		}

		Variant CountAggregator::collect () const
		{
			return Variant (this->count);
		}

		void CountAggregator::reset ()
		{
			this->count = 0;
		}

		bool CountAggregator::update (const Variant&)
		{
			++this->count;

			return true;
		}
	}
}

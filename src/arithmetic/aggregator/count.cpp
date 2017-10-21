
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

		Variant CountAggregator::compute () const
		{
			return Variant (this->count);
		}

		bool CountAggregator::push (const Variant&)
		{
			++this->count;

			return true;
		}

		void CountAggregator::reset ()
		{
			this->count = 0;
		}
	}
}

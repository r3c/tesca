
#include "last.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		LastAggregator::LastAggregator () :
			last ()
		{
		}

		Variant LastAggregator::collect () const
		{
			return this->last;
		}

		bool LastAggregator::update (Variant const& value)
		{
			// Minor optimization: save "keep" call when value didn't change
			if (this->last != value)
			{
				this->last = value;
				this->last.keep ();
			}

			return true;
		}
	}
}

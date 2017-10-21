
#include "min.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		MinAggregator::MinAggregator () :
			empty (true),
			min (0)
		{
		}

		Variant MinAggregator::compute () const
		{
			if (this->empty)
				return Variant::empty;

			return Variant (this->min);
		}

		bool MinAggregator::push (const Variant& value)
		{
			Float64 current;

			if (!value.toNumber (&current))
				return false;

			if (this->empty || current < this->min)
			{
				this->empty = false;
				this->min = current;
			}

			return true;
		}

		void MinAggregator::reset ()
		{
			this->empty = true;
			this->min = 0;
		}
	}
}

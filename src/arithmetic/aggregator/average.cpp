
#include "average.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		AverageAggregator::AverageAggregator ()
		{
			this->reset ();
		}

		Variant	AverageAggregator::compute () const
		{
			if (this->count > 0)
				return Variant (this->sum / this->count);

			return Variant::empty;
		}

		bool	AverageAggregator::push (const Variant& value)
		{
			Float64	number;

			if (!value.toNumber (&number))
				return false;

			this->sum += number;

			++this->count;

			return true;
		}

		void	AverageAggregator::reset ()
		{
			this->count = 0;
			this->sum = 0;
		}
	}
}

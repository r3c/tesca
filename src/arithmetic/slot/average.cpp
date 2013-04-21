
#include "average.hpp"

using namespace Glay;
using namespace Tesca::Provision;

namespace	Tesca
{
	namespace	Arithmetic
	{
		AverageSlot::AverageSlot ()
		{
			this->reset ();
		}

		Variant	AverageSlot::current () const
		{
			if (this->count > 0)
				return Variant (this->sum / this->count);

			return Variant::empty;
		}

		bool	AverageSlot::push (const Variant& value)
		{
			Float64	number;

			if (!value.toNumber (&number))
				return false;

			this->sum += number;

			++this->count;

			return true;
		}

		void	AverageSlot::reset ()
		{
			this->count = 0;
			this->sum = 0;
		}
	}
}

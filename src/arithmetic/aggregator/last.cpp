
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

		void LastAggregator::reset ()
		{
			this->last = Variant::empty;
		}

		bool LastAggregator::update (const Variant& value)
		{
			this->last = value;
			this->last.keep ();

			return true;
		}
	}
}

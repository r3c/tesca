
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

		Variant LastAggregator::compute () const
		{
			return this->last;
		}

		bool LastAggregator::push (const Variant& value)
		{
			this->last = value;
			this->last.keep ();

			return true;
		}

		void LastAggregator::reset ()
		{
			this->last = Variant::empty;
		}
	}
}

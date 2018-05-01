
#include "first.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		FirstAggregator::FirstAggregator () :
			empty (true),
			first ()
		{
		}

		Variant FirstAggregator::collect () const
		{
			return this->first;
		}

		bool FirstAggregator::update (Variant const& value)
		{
			if (this->empty)
			{
				this->empty = false;
				this->first = value;
				this->first.keep ();
			}

			return true;
		}
	}
}

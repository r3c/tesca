
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

		void FirstAggregator::reset ()
		{
			this->empty = true;
			this->first = Variant::empty;
		}

		bool FirstAggregator::update (const Variant& value)
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

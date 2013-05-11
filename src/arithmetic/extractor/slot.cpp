
#include "slot.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		SlotExtractor::SlotExtractor (Int32u slot) :
			slot (slot)
		{
		}

		Int32u	SlotExtractor::getFlags () const
		{
			return COMPOSITE;
		}

		Variant	SlotExtractor::compute (const Aggregator* const* aggregators) const
		{
			return aggregators[this->slot]->compute ();
		}

		Variant	SlotExtractor::extract (const Row&) const
		{
			return Variant::empty;
		}

		void	SlotExtractor::populate (Aggregator** aggregators) const
		{
			Extractor::populate (aggregators);

			aggregators[this->slot] = this->allocate ();
		}

		void	SlotExtractor::store (Aggregator** aggregators, const Provision::Row& row) const
		{
			Extractor::store (aggregators, row);

			aggregators[this->slot]->push (this->read (row));
		}
	}
}

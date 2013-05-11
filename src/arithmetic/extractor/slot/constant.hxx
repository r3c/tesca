
#include "reduce.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		template<typename T>
		ConstantSlotExtractor<T>::ConstantSlotExtractor (Int32u slot, const Variant& value) :
			SlotExtractor (slot),
			value (value)
		{
		}

		template<typename T>
		Aggregator*	ConstantSlotExtractor<T>::allocate () const
		{
			return new T ();
		}

		template<typename T>
		Variant	ConstantSlotExtractor<T>::read (const Row&) const
		{
			return this->value;
		}

		template<typename T>
		void	ConstantSlotExtractor<T>::recurse (RecurseCallback) const
		{
		}
	}
}

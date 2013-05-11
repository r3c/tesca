
#include "reduce.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		template<typename T>
		ReduceSlotExtractor<T>::ReduceSlotExtractor (Int32u slot, const Extractor* operand) :
			SlotExtractor (slot),
			operand (operand)
		{
		}

		template<typename T>
		Aggregator*	ReduceSlotExtractor<T>::allocate () const
		{
			return new T ();
		}

		template<typename T>
		Variant	ReduceSlotExtractor<T>::read (const Row& row) const
		{
			return this->operand->extract (row);
		}

		template<typename T>
		void	ReduceSlotExtractor<T>::recurse (RecurseCallback callback) const
		{
			callback (this->operand);
		}
	}
}

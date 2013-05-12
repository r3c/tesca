
#include "reduce.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		template<typename T>
		ReduceCompositeExtractor<T>::ReduceCompositeExtractor (Int32u slot, const Extractor* operand) :
			operand (operand),
			slot (slot)
		{
		}

		template<typename T>
		Variant	ReduceCompositeExtractor<T>::compute (const Aggregator* const* aggregators) const
		{
			return aggregators[this->slot]->compute ();
		}

		template<typename T>
		void	ReduceCompositeExtractor<T>::populate (Aggregator** aggregators) const
		{
			Extractor::populate (aggregators);

			aggregators[this->slot] = new T ();
		}

		template<typename T>
		void	ReduceCompositeExtractor<T>::recurse (RecurseCallback callback) const
		{
			callback (this->operand);
		}

		template<typename T>
		void	ReduceCompositeExtractor<T>::store (Aggregator** aggregators, const Provision::Row& row) const
		{
			Extractor::store (aggregators, row);

			aggregators[this->slot]->push (this->operand->extract (row));
		}
	}
}

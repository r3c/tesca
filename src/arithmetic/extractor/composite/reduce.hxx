
#include "reduce.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		template<typename T>
		ReduceCompositeExtractor<T>::ReduceCompositeExtractor (Int32u slot, const Extractor* operand, const string& prefix) :
			operand (operand),
			prefix (prefix),
			slot (slot)
		{
		}

		template<typename T>
		string ReduceCompositeExtractor<T>::createName (Int32u slot) const
		{
			return this->prefix + "_" + this->operand->createName (slot);
		}

		template<typename T>
		Variant	ReduceCompositeExtractor<T>::collect (Aggregator const* const* const aggregators) const
		{
			return aggregators[this->slot]->collect ();
		}

		template<typename T>
		void ReduceCompositeExtractor<T>::prepare (Aggregator** const aggregators) const
		{
			Extractor::prepare (aggregators);

			aggregators[this->slot] = new T ();
		}

		template<typename T>
		void ReduceCompositeExtractor<T>::recurse (RecurseCallback callback) const
		{
			callback (this->operand);
		}

		template<typename T>
		void ReduceCompositeExtractor<T>::update (Aggregator** const aggregators, const Provision::Row& row) const
		{
			Extractor::update (aggregators, row);

			aggregators[this->slot]->update (this->operand->extract (row));
		}
	}
}

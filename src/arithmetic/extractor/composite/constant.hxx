
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
		ConstantCompositeExtractor<T>::ConstantCompositeExtractor (Int32u slot, const Variant& value, const string& name) :
			name (name),
			slot (slot),
			value (value)
		{
		}

		template<typename T>
		string ConstantCompositeExtractor<T>::createName (Int32u) const
		{
			return this->name;
		}

		template<typename T>
		Variant	ConstantCompositeExtractor<T>::compute (const Aggregator* const* aggregators) const
		{
			return aggregators[this->slot]->compute ();
		}

		template<typename T>
		void ConstantCompositeExtractor<T>::populate (Aggregator** aggregators) const
		{
			Extractor::populate (aggregators);

			aggregators[this->slot] = new T ();
		}

		template<typename T>
		void ConstantCompositeExtractor<T>::recurse (RecurseCallback) const
		{
		}

		template<typename T>
		void ConstantCompositeExtractor<T>::store (Aggregator** aggregators, const Provision::Row& row) const
		{
			Extractor::store (aggregators, row);

			aggregators[this->slot]->push (this->value);
		}
	}
}

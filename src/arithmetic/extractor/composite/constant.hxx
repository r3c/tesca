
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
		ConstantCompositeExtractor<T>::ConstantCompositeExtractor (Int32u slot, Variant const& value, const string& name) :
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
		Variant	ConstantCompositeExtractor<T>::collect (Aggregator const* const* aggregators) const
		{
			return aggregators[this->slot]->collect ();
		}

		template<typename T>
		void ConstantCompositeExtractor<T>::prepare (Aggregator** aggregators) const
		{
			Extractor::prepare (aggregators);

			aggregators[this->slot] = new T ();
		}

		template<typename T>
		void ConstantCompositeExtractor<T>::recurse (RecurseCallback) const
		{
		}

		template<typename T>
		void ConstantCompositeExtractor<T>::update (Aggregator* const* aggregators, Provision::Row const& row) const
		{
			Extractor::update (aggregators, row);

			aggregators[this->slot]->update (this->value);
		}
	}
}

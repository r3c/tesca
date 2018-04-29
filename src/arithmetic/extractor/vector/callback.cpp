
#include "callback.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		CallbackVectorExtractor::CallbackVectorExtractor (const vector<const Extractor*>& extractors, const string& name, Callback callback) :
			VectorExtractor (extractors),
			callback (callback),
			name (name)
		{
		}

		string CallbackVectorExtractor::createName (Int32u) const
		{
			return this->name;
		}

		Variant CallbackVectorExtractor::compute (const Aggregator* const* aggregators) const
		{
			Variant values[this->length];

			for (auto i = this->length; i-- > 0; )
				values[i] = this->extractors[i]->compute (aggregators);

			return this->callback (values, this->length);
		}

		Variant CallbackVectorExtractor::extract (const Row& row) const
		{
			Variant values[this->length];

			for (auto i = this->length; i-- > 0; )
				values[i] = this->extractors[i]->extract (row);

			return this->callback (values, this->length);
		}
	}
}

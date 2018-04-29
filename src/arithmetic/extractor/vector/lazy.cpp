
#include "lazy.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		LazyVectorExtractor::LazyVectorExtractor (const vector<const Extractor*>& extractors, const string& name, Callback callback) :
			VectorExtractor (extractors),
			callback (callback),
			name (name)
		{
		}

		string LazyVectorExtractor::createName (Int32u) const
		{
			return this->name;
		}

		Variant LazyVectorExtractor::compute (const Aggregator* const* aggregators) const
		{
			return this->callback ([&] (Int32u i)
			{
				if (i >= this->length)
					return Variant::empty;

				return this->extractors[i]->compute (aggregators);
			}, this->length);
		}

		Variant LazyVectorExtractor::extract (const Row& row) const
		{
			return this->callback ([&] (Int32u i)
			{
				if (i >= this->length)
					return Variant::empty;

				return this->extractors[i]->extract (row);
			}, this->length);
		}
	}
}


#include "lazy.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		LazyVectorExtractor::LazyVectorExtractor (const vector<const Extractor*>& extractors, Callback callback) :
			VectorExtractor (extractors),
			callback (callback)
		{
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

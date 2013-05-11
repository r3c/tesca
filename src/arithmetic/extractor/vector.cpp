
#include "vector.hpp"

using namespace std;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		VectorExtractor::VectorExtractor (const vector<const Extractor*>& extractors) :
			extractors (new const Extractor*[extractors.size ()]),
			length (extractors.size ())
		{
			for (auto i = extractors.size (); i-- > 0; )
				this->extractors[i] = extractors[i];
		}

		VectorExtractor::~VectorExtractor ()
		{
			delete [] this->extractors;
		}

		Variant	VectorExtractor::compute (const Aggregator* const* aggregators) const
		{
			Variant	values[this->length];

			for (auto i = this->length; i-- > 0; )
				values[i] = this->extractors[i]->compute (aggregators);

			return this->evaluate (values, this->length);
		}

		Variant	VectorExtractor::extract (const Row& row) const
		{
			Variant	values[this->length];

			for (auto i = this->length; i-- > 0; )
				values[i] = this->extractors[i]->extract (row);

			return this->evaluate (values, this->length);
		}

		void	VectorExtractor::recurse (RecurseCallback callback) const
		{
			for (auto i = this->length; i-- > 0; )
				callback (this->extractors[i]);
		}
	}
}

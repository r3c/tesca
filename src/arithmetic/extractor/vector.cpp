
#include "vector.hpp"

using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		VectorExtractor::VectorExtractor (const vector<Extractor const*>& extractors) :
			extractors (new Extractor const*[extractors.size ()]),
			length (extractors.size ())
		{
			for (auto i = extractors.size (); i-- > 0; )
				this->extractors[i] = extractors[i];
		}

		VectorExtractor::~VectorExtractor ()
		{
			delete [] this->extractors;
		}

		void VectorExtractor::recurse (RecurseCallback callback) const
		{
			for (auto i = this->length; i-- > 0; )
				callback (this->extractors[i]);
		}
	}
}

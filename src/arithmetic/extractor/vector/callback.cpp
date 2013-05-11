
#include "callback.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		CallbackVectorExtractor::CallbackVectorExtractor (const vector<const Extractor*>& extractors, Callback callback) :
			VectorExtractor (extractors),
			callback (callback)
		{
		}

		Variant	CallbackVectorExtractor::evaluate (const Variant* values, Int32u length) const
		{
			return this->callback (values, length);
		}
	}
}

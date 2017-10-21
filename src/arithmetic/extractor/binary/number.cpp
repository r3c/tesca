
#include "number.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		NumberBinaryExtractor::NumberBinaryExtractor (const Extractor* lhs, const Extractor* rhs, Callback callback) :
			BinaryExtractor (lhs, rhs),
			callback (callback)
		{
		}

		Variant NumberBinaryExtractor::evaluate (const Variant& lhs, const Variant& rhs) const
		{
			Float64 a;
			Float64 b;

			if (lhs.toNumber (&a) && rhs.toNumber (&b))
				return this->callback (a, b);

			return Variant::empty;
		}
	}
}

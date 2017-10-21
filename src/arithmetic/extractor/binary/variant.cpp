
#include "variant.hpp"

using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		VariantBinaryExtractor::VariantBinaryExtractor (const Extractor* lhs, const Extractor* rhs, Callback callback) :
			BinaryExtractor (lhs, rhs),
			callback (callback)
		{
		}

		Variant VariantBinaryExtractor::evaluate (const Variant& lhs, const Variant& rhs) const
		{
			return this->callback (lhs, rhs);
		}
	}
}

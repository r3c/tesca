
#include "variant.hpp"

using namespace Glay;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		VariantBinaryExtractor::VariantBinaryExtractor (const Extractor* lhs, const Extractor* rhs, const string& infix, Callback callback) :
			BinaryExtractor (lhs, rhs, infix),
			callback (callback)
		{
		}

		Variant VariantBinaryExtractor::evaluate (const Variant& lhs, const Variant& rhs) const
		{
			return this->callback (lhs, rhs);
		}
	}
}

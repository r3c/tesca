
#include "callback.hpp"

using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		CallbackBinaryExtractor::CallbackBinaryExtractor (const Extractor* lhs, const Extractor* rhs, Callback callback) :
			BinaryExtractor (lhs, rhs),
			callback (callback)
		{
		}

		Variant	CallbackBinaryExtractor::evaluate (const Variant& lhs, const Variant& rhs) const
		{
			return this->callback (lhs, rhs);
		}
	}
}

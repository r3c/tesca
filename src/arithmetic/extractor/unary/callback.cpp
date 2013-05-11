
#include "callback.hpp"

using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		CallbackUnaryExtractor::CallbackUnaryExtractor (const Extractor* source, Callback callback) :
			UnaryExtractor (source),
			callback (callback)
		{
		}

		Variant	CallbackUnaryExtractor::evaluate (const Variant& argument) const
		{
			return this->callback (argument);
		}
	}
}


#include "callback.hpp"

using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		CallbackUnaryAccessor::CallbackUnaryAccessor (const Accessor* source, Callback callback) :
			UnaryAccessor (source),
			callback (callback)
		{
		}

		Variant	CallbackUnaryAccessor::evaluate (const Variant& argument) const
		{
			return this->callback (argument);
		}
	}
}

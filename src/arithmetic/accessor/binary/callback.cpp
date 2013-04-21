
#include "callback.hpp"

using namespace Tesca::Provision;

namespace	Tesca
{
	namespace	Arithmetic
	{
		CallbackBinaryAccessor::CallbackBinaryAccessor (const Accessor* lhs, const Accessor* rhs, Callback callback) :
			BinaryAccessor (lhs, rhs),
			callback (callback)
		{
		}

		Variant	CallbackBinaryAccessor::evaluate (const Variant& lhs, const Variant& rhs) const
		{
			return this->callback (lhs, rhs);
		}
	}
}

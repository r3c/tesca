
#include "callback.hpp"

namespace	Tesca
{
	CallbackUnaryAccessor::CallbackUnaryAccessor (const Accessor* source, const Callback* callback) :
		UnaryAccessor (source),
		callback (callback)
	{
	}

	Variant	CallbackUnaryAccessor::evaluate (const Variant& argument) const
	{
		return (*this->callback) (argument);
	}
}

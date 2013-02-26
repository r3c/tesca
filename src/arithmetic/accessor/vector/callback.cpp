
#include "callback.hpp"

namespace	Tesca
{
	CallbackVectorAccessor::CallbackVectorAccessor (const Accessors& accessors, Callback callback) :
		VectorAccessor (accessors),
		callback (callback)
	{
	}

	Variant	CallbackVectorAccessor::evaluate (const Values& values) const
	{
		return this->callback (values);
	}
}


#include "number.hpp"

using namespace Glay;

namespace	Tesca
{
	NumberBinaryAccessor::NumberBinaryAccessor (const Accessor* lhs, const Accessor* rhs, const Callback* callback) :
		BinaryAccessor (lhs, rhs),
		callback (callback)
	{
	}

	Variant	NumberBinaryAccessor::evaluate (const Variant& lhs, const Variant& rhs) const
	{
		Float64	a;
		Float64	b;

		if (lhs.toNumber (&a) && rhs.toNumber (&b))
			return (*this->callback) (a, b);

		return Variant::empty;
	}
}

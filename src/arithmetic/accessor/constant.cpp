
#include "constant.hpp"

namespace	Tesca
{
	ConstantAccessor::ConstantAccessor (const Variant& constant) :
		constant (constant)
	{
	}

	Variant	ConstantAccessor::read (const Row&) const
	{
		return this->constant;
	}
}

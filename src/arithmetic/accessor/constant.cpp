
#include "constant.hpp"

using namespace Tesca::Provision;

namespace	Tesca
{
	ConstantAccessor::ConstantAccessor (const Variant& constant) :
		constant (constant)
	{
		this->constant.keep ();
	}

	Variant	ConstantAccessor::read (const Row&) const
	{
		return this->constant;
	}
}

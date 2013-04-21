
#include "constant.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
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
}

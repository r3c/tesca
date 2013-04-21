
#include "or.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		OrLogicalAccessor::OrLogicalAccessor (const Accessor* lhs, const Accessor* rhs) :
			LogicalAccessor (lhs, rhs)
		{
		}

		Variant	OrLogicalAccessor::read (const Row& row) const
		{
			return Variant (this->testLHS (row) || this->testRHS (row));
		}
	}
}

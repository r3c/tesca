
#include "and.hpp"

namespace	Tesca
{
	AndLogicalAccessor::AndLogicalAccessor (const Accessor* lhs, const Accessor* rhs) :
		LogicalAccessor (lhs, rhs)
	{
	}

	Variant	AndLogicalAccessor::read (const Row& row) const
	{
		return Variant (this->testLHS (row) && this->testRHS (row));
	}
}


#include "or.hpp"

using namespace Tesca::Stream;

namespace	Tesca
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

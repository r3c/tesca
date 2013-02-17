
#include "binary.hpp"

namespace	Tesca
{
	BinaryAccessor::BinaryAccessor (const Accessor* lhs, const Accessor* rhs) :
		lhs (lhs),
		rhs (rhs)
	{
	}

	Variant	BinaryAccessor::read (const Row& row) const
	{
		return this->evaluate (this->lhs->read (row), this->rhs->read (row));
	}
}

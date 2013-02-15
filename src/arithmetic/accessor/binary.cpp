
#include "binary.hpp"

namespace	Tesca
{
	BinaryAccessor::BinaryAccessor (const Accessor* lhs, const Accessor* rhs, const Evaluator* evaluator) :
		evaluator (evaluator),
		lhs (lhs),
		rhs (rhs)
	{
	}

	Variant	BinaryAccessor::read (const Row& row) const
	{
		return (*this->evaluator) (this->lhs->read (row), this->rhs->read (row));
	}
}

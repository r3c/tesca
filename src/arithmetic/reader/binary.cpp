
#include "binary.hpp"

namespace	Tesca
{
	BinaryReader::BinaryReader (const Reader* lhs, const Reader* rhs, const Evaluator* evaluator) :
		evaluator (evaluator),
		lhs (lhs),
		rhs (rhs)
	{
	}

	Variant	BinaryReader::read (const Row& row) const
	{
		return (*this->evaluator) (this->lhs->read (row), this->rhs->read (row));
	}
}

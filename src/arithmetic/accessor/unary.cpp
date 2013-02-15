
#include "unary.hpp"

namespace	Tesca
{
	UnaryAccessor::UnaryAccessor (const Accessor* source, const Evaluator* evaluator) :
		evaluator (evaluator),
		source (source)
	{
	}

	Variant	UnaryAccessor::read (const Row& row) const
	{
		return (*this->evaluator) (this->source->read (row));
	}
}

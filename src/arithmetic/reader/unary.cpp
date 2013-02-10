
#include "unary.hpp"

namespace	Tesca
{
	UnaryReader::UnaryReader (const Reader* source, const Evaluator* evaluator) :
		evaluator (evaluator),
		source (source)
	{
	}

	Variant	UnaryReader::read (const Row& row) const
	{
		return (*this->evaluator) (this->source->read (row));
	}
}

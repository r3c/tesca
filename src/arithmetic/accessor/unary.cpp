
#include "unary.hpp"

using namespace Tesca::Stream;

namespace	Tesca
{
	UnaryAccessor::UnaryAccessor (const Accessor* source) :
		source (source)
	{
	}

	Variant	UnaryAccessor::read (const Row& row) const
	{
		return this->evaluate (this->source->read (row));
	}
}

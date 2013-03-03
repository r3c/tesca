
#include "unary.hpp"

using namespace Tesca::Provision;

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

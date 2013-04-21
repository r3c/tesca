
#include "binary.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
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
}

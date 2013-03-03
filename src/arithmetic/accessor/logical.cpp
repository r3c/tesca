
#include "logical.hpp"

using namespace Tesca::Provision;

namespace	Tesca
{
	LogicalAccessor::LogicalAccessor (const Accessor* lhs, const Accessor* rhs) :
		lhs (lhs),
		rhs (rhs)
	{
	}

	bool	LogicalAccessor::testLHS (const Row& row) const
	{
		bool	test;

		return this->lhs->read (row).toBoolean (&test) && test;
	}

	bool	LogicalAccessor::testRHS (const Row& row) const
	{
		bool	test;

		return this->rhs->read (row).toBoolean (&test) && test;
	}
}

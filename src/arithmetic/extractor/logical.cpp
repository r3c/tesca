
#include "logical.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		LogicalExtractor::LogicalExtractor (Extractor const* lhs, Extractor const* rhs) :
			lhs (lhs),
			rhs (rhs)
		{
		}

		bool LogicalExtractor::collectLHS (Aggregator const* const* aggregators) const
		{
			bool test;

			return this->lhs->collect (aggregators).toBoolean (&test) && test;
		}

		bool LogicalExtractor::collectRHS (Aggregator const* const* aggregators) const
		{
			bool test;

			return this->lhs->collect (aggregators).toBoolean (&test) && test;
		}

		bool LogicalExtractor::extractLHS (Row const& row) const
		{
			bool test;

			return this->lhs->extract (row).toBoolean (&test) && test;
		}

		bool LogicalExtractor::extractRHS (Row const& row) const
		{
			bool test;

			return this->rhs->extract (row).toBoolean (&test) && test;
		}

		void LogicalExtractor::recurse (RecurseCallback callback) const
		{
			callback (this->lhs);
			callback (this->rhs);
		}
	}
}

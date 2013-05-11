
#include "and.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		AndLogicalExtractor::AndLogicalExtractor (const Extractor* lhs, const Extractor* rhs) :
			LogicalExtractor (lhs, rhs)
		{
		}

		Variant	AndLogicalExtractor::compute (const Aggregator* const* aggregators) const
		{
			return Variant (this->computeLHS (aggregators) && this->computeRHS (aggregators));
		}

		Variant	AndLogicalExtractor::extract (const Row& row) const
		{
			return Variant (this->extractLHS (row) && this->extractRHS (row));
		}
	}
}

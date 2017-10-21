
#include "or.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		OrLogicalExtractor::OrLogicalExtractor (const Extractor* lhs, const Extractor* rhs) :
			LogicalExtractor (lhs, rhs)
		{
		}

		Variant OrLogicalExtractor::compute (const Aggregator* const* aggregators) const
		{
			return Variant (this->computeLHS (aggregators) || this->computeRHS (aggregators));
		}

		Variant OrLogicalExtractor::extract (const Row& row) const
		{
			return Variant (this->extractLHS (row) || this->extractRHS (row));
		}
	}
}

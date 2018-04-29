
#include "and.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		AndLogicalExtractor::AndLogicalExtractor (const Extractor* lhs, const Extractor* rhs) :
			LogicalExtractor (lhs, rhs)
		{
		}

		string AndLogicalExtractor::createName (Int32u slot) const
		{
			return this->lhs->createName (slot) + "_and_" + this->rhs->createName (slot);
		}

		Variant AndLogicalExtractor::compute (const Aggregator* const* aggregators) const
		{
			return Variant (this->computeLHS (aggregators) && this->computeRHS (aggregators));
		}

		Variant AndLogicalExtractor::extract (const Row& row) const
		{
			return Variant (this->extractLHS (row) && this->extractRHS (row));
		}
	}
}

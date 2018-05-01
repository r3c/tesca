
#include "and.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		AndLogicalExtractor::AndLogicalExtractor (Extractor const* lhs, Extractor const* rhs) :
			LogicalExtractor (lhs, rhs)
		{
		}

		string AndLogicalExtractor::createName (Int32u slot) const
		{
			return this->lhs->createName (slot) + "_and_" + this->rhs->createName (slot);
		}

		Variant AndLogicalExtractor::collect (Aggregator const* const* aggregators) const
		{
			return Variant (this->collectLHS (aggregators) && this->collectRHS (aggregators));
		}

		Variant AndLogicalExtractor::extract (Row const& row) const
		{
			return Variant (this->extractLHS (row) && this->extractRHS (row));
		}
	}
}

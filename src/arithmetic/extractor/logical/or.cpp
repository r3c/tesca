
#include "or.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		OrLogicalExtractor::OrLogicalExtractor (Extractor const* lhs, Extractor const* rhs) :
			LogicalExtractor (lhs, rhs)
		{
		}

		string OrLogicalExtractor::createName (Int32u slot) const
		{
			return this->lhs->createName (slot) + "_or_" + this->rhs->createName (slot);
		}

		Variant OrLogicalExtractor::collect (Aggregator const* const* aggregators) const
		{
			return Variant (this->collectLHS (aggregators) || this->collectRHS (aggregators));
		}

		Variant OrLogicalExtractor::extract (Row const& row) const
		{
			return Variant (this->extractLHS (row) || this->extractRHS (row));
		}
	}
}

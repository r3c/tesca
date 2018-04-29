
#include "or.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		OrLogicalExtractor::OrLogicalExtractor (const Extractor* lhs, const Extractor* rhs) :
			LogicalExtractor (lhs, rhs)
		{
		}

		string OrLogicalExtractor::createName (Int32u slot) const
		{
			return this->lhs->createName (slot) + "_or_" + this->rhs->createName (slot);
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

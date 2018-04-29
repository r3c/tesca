
#include "binary.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		BinaryExtractor::BinaryExtractor (const Extractor* lhs, const Extractor* rhs, const string& infix) :
			infix (infix),
			lhs (lhs),
			rhs (rhs)
		{
		}

		string BinaryExtractor::createName (Int32u slot) const
		{
			return this->lhs->createName (slot) + "_" + this->infix + "_" + this->rhs->createName (slot);
		}

		Variant BinaryExtractor::compute (const Aggregator* const* aggregators) const
		{
			return this->evaluate (this->lhs->compute (aggregators), this->rhs->compute (aggregators));
		}

		Variant BinaryExtractor::extract (const Row& row) const
		{
			return this->evaluate (this->lhs->extract (row), this->rhs->extract (row));
		}

		void BinaryExtractor::recurse (RecurseCallback callback) const
		{
			callback (this->lhs);
			callback (this->rhs);
		}
	}
}

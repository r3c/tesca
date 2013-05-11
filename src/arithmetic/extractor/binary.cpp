
#include "binary.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		BinaryExtractor::BinaryExtractor (const Extractor* lhs, const Extractor* rhs) :
			lhs (lhs),
			rhs (rhs)
		{
		}

		Variant	BinaryExtractor::compute (const Aggregator* const* aggregators) const
		{
			return this->evaluate (this->lhs->compute (aggregators), this->rhs->compute (aggregators));
		}

		Variant	BinaryExtractor::extract (const Row& row) const
		{
			return this->evaluate (this->lhs->extract (row), this->rhs->extract (row));
		}

		void	BinaryExtractor::recurse (RecurseCallback callback) const
		{
			callback (this->lhs);
			callback (this->rhs);
		}
	}
}

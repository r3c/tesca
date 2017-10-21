
#include "unary.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		UnaryExtractor::UnaryExtractor (const Extractor* operand) :
			operand (operand)
		{
		}

		Variant UnaryExtractor::compute (const Aggregator* const* aggregators) const
		{
			return this->evaluate (this->operand->compute (aggregators));
		}

		Variant UnaryExtractor::extract (const Row& row) const
		{
			return this->evaluate (this->operand->extract (row));
		}

		void UnaryExtractor::recurse (RecurseCallback callback) const
		{
			callback (this->operand);
		}
	}
}


#include "unary.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		UnaryExtractor::UnaryExtractor (const Extractor* operand, const string& prefix) :
			operand (operand),
			prefix (prefix)
		{
		}

		string UnaryExtractor::createName (Int32u slot) const
		{
			return this->prefix + "_" + this->operand->createName (slot);
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

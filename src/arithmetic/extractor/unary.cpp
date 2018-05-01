
#include "unary.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		UnaryExtractor::UnaryExtractor (Extractor const* operand, const string& prefix, Callback callback) :
			callback (callback),
			operand (operand),
			prefix (prefix)
		{
		}

		string UnaryExtractor::createName (Int32u slot) const
		{
			return this->prefix + "_" + this->operand->createName (slot);
		}

		Variant UnaryExtractor::collect (Aggregator const* const* aggregators) const
		{
			return this->callback (this->operand->collect (aggregators));
		}

		Variant UnaryExtractor::extract (Row const& row) const
		{
			return this->callback (this->operand->extract (row));
		}

		void UnaryExtractor::recurse (RecurseCallback callback) const
		{
			callback (this->operand);
		}
	}
}

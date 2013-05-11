
#include "constant.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		ConstantExtractor::ConstantExtractor (const Variant& value) :
			value (value)
		{
			this->value.keep ();
		}

		Variant	ConstantExtractor::compute (const Aggregator* const*) const
		{
			return this->value;
		}

		Variant	ConstantExtractor::extract (const Row&) const
		{
			return this->value;
		}
	}
}

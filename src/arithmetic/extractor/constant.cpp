
#include "constant.hpp"

using namespace Glay;
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

		Int32u	ConstantExtractor::getFlags () const
		{
			return COMPOSITE | SCALAR;
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

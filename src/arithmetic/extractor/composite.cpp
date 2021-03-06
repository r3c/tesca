
#include "composite.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		Int32u CompositeExtractor::getFlags () const
		{
			return COMPOSITE;
		}

		Variant CompositeExtractor::extract (Row const&) const
		{
			return Variant::empty;
		}
	}
}

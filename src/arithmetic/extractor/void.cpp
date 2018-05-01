
#include "void.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		VoidExtractor const VoidExtractor::instance = VoidExtractor ();

		string VoidExtractor::createName (Int32u) const
		{
			return "void";
		}

		Int32u VoidExtractor::getFlags () const
		{
			return COMPOSITE | SCALAR;
		}

		Variant VoidExtractor::collect (Aggregator const* const*) const
		{
			return Variant::empty;
		}

		Variant VoidExtractor::extract (Row const&) const
		{
			return Variant::empty;
		}
	}
}

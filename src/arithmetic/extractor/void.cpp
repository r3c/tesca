
#include "void.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		const VoidExtractor VoidExtractor::instance = VoidExtractor ();

		string VoidExtractor::createName (Int32u) const
		{
			return "void";
		}

		Int32u VoidExtractor::getFlags () const
		{
			return COMPOSITE | SCALAR;
		}

		Variant VoidExtractor::compute (const Aggregator* const*) const
		{
			return Variant::empty;
		}

		Variant VoidExtractor::extract (const Row&) const
		{
			return Variant::empty;
		}
	}
}

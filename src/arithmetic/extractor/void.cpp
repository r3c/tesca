
#include "void.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		const VoidExtractor	VoidExtractor::instance = VoidExtractor ();

		Int32u	VoidExtractor::getFlags () const
		{
			return COMPOSITE | SCALAR;
		}

		Variant	VoidExtractor::compute (const Aggregator* const*) const
		{
			return Variant::empty;
		}

		Variant	VoidExtractor::extract (const Row&) const
		{
			return Variant::empty;
		}
	}
}

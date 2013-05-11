
#include "void.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		const VoidExtractor	VoidExtractor::instance = VoidExtractor ();

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

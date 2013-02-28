
#include "void.hpp"

using namespace Tesca::Stream;

namespace	Tesca
{
	const VoidAccessor	VoidAccessor::instance = VoidAccessor ();

	Variant	VoidAccessor::read (const Row&) const
	{
		return Variant::empty;
	}
}

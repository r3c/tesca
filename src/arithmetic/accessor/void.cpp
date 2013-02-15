
#include "void.hpp"

namespace	Tesca
{
	const VoidAccessor	VoidAccessor::instance = VoidAccessor ();

	Variant	VoidAccessor::read (const Row&) const
	{
		return Variant::empty;
	}
}


#include "void.hpp"

namespace	Tesca
{
	const VoidReader	VoidReader::instance = VoidReader ();

	Variant	VoidReader::read (const Row&) const
	{
		return Variant::empty;
	}
}

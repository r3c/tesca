
#include "void.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		const VoidAccessor	VoidAccessor::instance = VoidAccessor ();

		Variant	VoidAccessor::read (const Row&) const
		{
			return Variant::empty;
		}
	}
}

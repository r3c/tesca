
#include "constant.hpp"

using namespace Tesca::Storage;

namespace Tesca
{
	namespace Expression
	{
		Constant const Constant::constants[] =
		{
			{"false",	Variant (false)},
			{"true",	Variant (true)},
			{"void",	Variant ()},
			{0, 		Variant ()}
		};
	}
}

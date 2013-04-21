
#include "constant.hpp"

using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Expression
	{
		const Constant	Constant::constants[] =
		{
			{"false",	[] () -> Variant
			{
				return Variant (false);
			}},
			{"true",	[] () -> Variant
			{
				return Variant (true);
			}},
			{"void",	[] () -> Variant
			{
				return Variant ();
			}},
			{0, 0}
		};
	}
}

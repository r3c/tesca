
#ifndef __TESCA_EXPRESSION_CONSTANT_HPP
#define __TESCA_EXPRESSION_CONSTANT_HPP

#include "../storage/variant.hpp"

namespace Tesca
{
	namespace Expression
	{
		struct Constant
		{
			static Constant const constants[];

			const char* name;
			Storage::Variant value;
		};
	}
}

#endif

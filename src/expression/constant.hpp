
#ifndef __TESCA_EXPRESSION_CONSTANT_HPP
#define __TESCA_EXPRESSION_CONSTANT_HPP

#include <functional>
#include "../provision/variant.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		struct	Constant
		{
			typedef std::function<Provision::Variant ()>	Builder;

			static const Constant	constants[];

			const char*	name;
			Builder		builder;
		};
	}
}

#endif

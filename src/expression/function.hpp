
#ifndef __TESCA_EXPRESSION_FUNCTION_HPP
#define __TESCA_EXPRESSION_FUNCTION_HPP

#include <functional>
#include <vector>
#include "../../lib/glay/src/include.hpp"
#include "../arithmetic/accessor.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		struct	Function
		{
			typedef std::function<Accessor* (const std::vector<const Accessor*>&)>	Builder;

			static const Function	functions[];

			const char*		name;
			Glay::Int32u	min;
			Glay::Int32u	max;
			Builder			builder;
		};
	}
}

#endif


#ifndef __TESCA_EXPRESSION_FUNCTION_HPP
#define __TESCA_EXPRESSION_FUNCTION_HPP

#include <cmath>
#include <functional>
#include <vector>
#include "../arithmetic/accessor.hpp"
#include "../glay/glay.hpp"

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

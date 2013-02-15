
#ifndef __TESCA_EXPRESSION_FUNCTION_HPP
#define __TESCA_EXPRESSION_FUNCTION_HPP

#include <vector>
#include "../arithmetic/accessor.hpp"
#include "../glay/glay.hpp"

namespace	Tesca
{
	struct	Function
	{
		typedef Accessor*	(*Builder) (const std::vector<const Accessor*>&);

		static const Function	functions[];

		const char*		name;
		Glay::Int32u	count;
		Builder			builder;
	};
}

#endif

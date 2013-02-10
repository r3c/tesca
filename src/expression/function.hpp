
#ifndef __TESCA_EXPRESSION_FUNCTION_HPP
#define __TESCA_EXPRESSION_FUNCTION_HPP

#include <vector>
#include "../arithmetic/reader.hpp"
#include "../glay/glay.hpp"

namespace	Tesca
{
	struct	Function
	{
		typedef Reader*	(*Builder) (const std::vector<Reader*>&);

		static const Function	functions[];

		const char*		name;
		Glay::Int32u	count;
		Builder			builder;
	};
}

#endif

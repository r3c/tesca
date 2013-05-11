
#ifndef __TESCA_EXPRESSION_FUNCTION_HPP
#define __TESCA_EXPRESSION_FUNCTION_HPP

#include <functional>
#include <vector>
#include "../../lib/glay/src/include.hpp"
#include "../arithmetic/extractor.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		struct	Function
		{
			typedef std::function<Arithmetic::Extractor* (const std::vector<const Arithmetic::Extractor*>&, Glay::Int32u*)>	Builder;

			static const Function	functions[];

			const char*		name;
			Glay::Int32u	min;
			Glay::Int32u	max;
			Builder			builder;
		};
	}
}

#endif

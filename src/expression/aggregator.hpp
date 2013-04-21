
#ifndef __TESCA_EXPRESSION_AGGREGATOR_HPP
#define __TESCA_EXPRESSION_AGGREGATOR_HPP

#include <functional>
#include <string>
#include "../arithmetic/accessor.hpp"
#include "../arithmetic/column.hpp"

namespace	Tesca
{
	namespace	Expression
	{
		struct	Aggregator
		{
			typedef std::function<Arithmetic::Column* (const std::string&, const Arithmetic::Accessor*)>	Builder;

			static const Aggregator	aggregators[];

			const char*	name;
			Builder		builder;
		};
	}
}

#endif

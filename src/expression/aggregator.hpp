
#ifndef __TESCA_EXPRESSION_AGGREGATOR_HPP
#define __TESCA_EXPRESSION_AGGREGATOR_HPP

#include <string>
#include "../arithmetic/accessor.hpp"
#include "../arithmetic/column.hpp"

namespace	Tesca
{
	struct	Aggregator
	{
		typedef Column*	(*Builder) (const std::string&, const Accessor*);

		static const Aggregator	aggregators[];

		const char*	name;
		Builder		builder;
	};
}

#endif

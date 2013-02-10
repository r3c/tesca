
#ifndef __TESCA_EXPRESSION_AGGREGATOR_HPP
#define __TESCA_EXPRESSION_AGGREGATOR_HPP

#include <string>
#include "../arithmetic/column.hpp"
#include "../arithmetic/reader.hpp"

namespace	Tesca
{
	struct	Aggregator
	{
		typedef Column*	(*Builder) (const std::string&, const Reader*);

		static const Aggregator	aggregators[];

		const char*	name;
		Builder		builder;
	};
}

#endif

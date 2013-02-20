
#ifndef __TESCA_STREAM_PARSER_HPP
#define __TESCA_STREAM_PARSER_HPP

#include <functional>
#include "../glay/glay.hpp"
#include "reader.hpp"

namespace	Tesca
{
	struct	Parser
	{
		typedef std::function<Reader* (Glay::Pipe::IStream*, const Reader::Fields*, const char*)>	Builder;

		static const Parser	parsers[];

		const char*	name;
		Builder		builder;
	};
}

#endif

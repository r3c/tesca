
#ifndef __TESCA_STREAM_PARSER_HPP
#define __TESCA_STREAM_PARSER_HPP

#include <functional>
#include <map>
#include <string>
#include "../glay/glay.hpp"
#include "reader.hpp"

namespace	Tesca
{
	struct	Parser
	{
		typedef std::map<std::string, std::string>	Config;
		typedef std::function<Reader* (Glay::Pipe::IStream*, const Reader::Fields&, const Config&)>	Builder;

		static const Parser	parsers[];

		const char*	name;
		Builder		builder;
	};
}

#endif

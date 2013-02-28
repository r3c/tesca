
#ifndef __TESCA_STREAM_PARSER_HPP
#define __TESCA_STREAM_PARSER_HPP

#include <functional>
#include <map>
#include <string>
#include "../glay/glay.hpp"
#include "lookup.hpp"
#include "reader.hpp"

namespace	Tesca
{
	namespace	Stream
	{
		struct	Parser
		{
			typedef std::map<std::string, std::string>	Config;
			typedef std::function<Reader* (Glay::Pipe::IStream*, const Lookup&, const Config&)>	Builder;

			static const Parser	parsers[];

			const char*	name;
			Builder		builder;
		};
	}
}

#endif


#ifndef __TESCA_PROVISION_PARSER_HPP
#define __TESCA_PROVISION_PARSER_HPP

#include <functional>
#include <map>
#include <string>
#include "../../lib/glay/src/glay.hpp"
#include "config.hpp"
#include "lookup.hpp"
#include "reader.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		struct	Parser
		{
			typedef std::function<Reader* (Glay::Pipe::IStream*, const Lookup&, const Config&)>	Builder;

			static const Parser	parsers[];

			const char*	name;
			Builder		builder;
		};
	}
}

#endif


#ifndef __TESCA_PROVISION_FORMAT_HPP
#define __TESCA_PROVISION_FORMAT_HPP

#include <functional>
#include "../../lib/glay/src/include.hpp"
#include "config.hpp"
#include "lookup.hpp"
#include "reader.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		struct	Format
		{
			typedef std::function<Reader* (Glay::Pipe::IStream*, const Lookup&, const Config&)>	Builder;

			static const Format	formats[];

			const char*	name;
			Builder		builder;
		};
	}
}

#endif

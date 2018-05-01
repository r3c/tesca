
#ifndef __TESCA_PROVISION_FORMAT_HPP
#define __TESCA_PROVISION_FORMAT_HPP

#include <functional>
#include "../../lib/glay/src/glay.hpp"
#include "../storage/config.hpp"
#include "lookup.hpp"
#include "reader.hpp"

namespace Tesca
{
	namespace Provision
	{
		struct Format
		{
			typedef std::function<Reader* (Glay::Pipe::SeekIStream*, Lookup const&, Storage::Config const&)> Builder;

			static Format const formats[];

			const char* name;
			Builder builder;
		};
	}
}

#endif

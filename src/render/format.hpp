
#ifndef __TESCA_RENDER_FORMAT_HPP
#define __TESCA_RENDER_FORMAT_HPP

#include <functional>
#include "../../lib/glay/src/glay.hpp"
#include "../storage/config.hpp"
#include "printer.hpp"

namespace Tesca
{
	namespace Render
	{
		struct Format
		{
			typedef std::function<Printer* (const Storage::Config&)> Builder;

			static const Format formats[];

			const char* name;
			Builder builder;
		};
	}
}

#endif

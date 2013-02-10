
#ifndef __TESCA_ROW_HPP
#define __TESCA_ROW_HPP

#include <map>
#include <string>
#include "../glay/glay.hpp"
#include "variant.hpp"

namespace	Tesca
{
	class	Row
	{
// FIXME
public:
	/**/			Row (const std::map<std::string, const Variant*>&);
private:
	const std::map<std::string, const Variant*>&	values;
// FIXME

		public:
			/**/			Row (const Row&);

			Row&			operator = (const Row&);
			const Variant&	operator [] (std::string) const;
	};
}

#endif

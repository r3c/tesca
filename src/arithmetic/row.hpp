
#ifndef __TESCA_ROW_HPP
#define __TESCA_ROW_HPP

#include <map>
#include <string>
#include "../glay/glay.hpp"
#include "value.hpp"

namespace	Tesca
{
	class	Row
	{
// FIXME
public:
	/**/			Row (const std::map<std::string, const Value*>&);
private:
	const std::map<std::string, const Value*>&	values;
// FIXME

		public:
			/**/			Row (const Row&);

			Row&			operator = (const Row&);
			const Value&	operator [] (std::string) const;
	};
}

#endif

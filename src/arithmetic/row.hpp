
#ifndef __TESCA_ROW_HPP
#define __TESCA_ROW_HPP

#include "../glay/glay.hpp"
#include "value.hpp"

namespace	Tesca
{
	class	Row
	{
// FIXME
public:
	/**/			Row (const Value**);
private:
	const Value**	values;
// FIXME

		public:
			/**/			Row (const Row&);
			/**/			Row ();

			Row&			operator = (const Row&);
			const Value&	operator [] (Glay::Int32u) const;
	};
}

#endif

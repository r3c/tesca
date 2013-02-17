
#ifndef __TESCA_ROW_HPP
#define __TESCA_ROW_HPP

#include "../glay/glay.hpp"
#include "variant.hpp"

namespace	Tesca
{
	class	Row
	{
		public:
			Row (const Row&);
			Row ();

			Row&					operator = (const Row&);
			virtual const Variant&	operator [] (Glay::Int32u) const = 0;
	};
}

#endif

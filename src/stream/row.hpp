
#ifndef __TESCA_STREAM_ROW_HPP
#define __TESCA_STREAM_ROW_HPP

#include "../glay/glay.hpp"
#include "variant.hpp"

namespace	Tesca
{
	class	Row
	{
		public:
					Row (const Row&);
					Row ();
			virtual	~Row ();

			Row&					operator = (const Row&);
			virtual const Variant&	operator [] (Glay::Int32u) const = 0;
	};
}

#endif

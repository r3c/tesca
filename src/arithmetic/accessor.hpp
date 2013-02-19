
#ifndef __TESCA_ACCESSOR_HPP
#define __TESCA_ACCESSOR_HPP

#include "../stream/row.hpp"
#include "../stream/variant.hpp"

namespace	Tesca
{
	class	Accessor
	{
		public:
			virtual	~Accessor ();

			virtual Variant	read (const Row&) const = 0;
	};
}

#endif


#ifndef __TESCA_ARITHMETIC_ACCESSOR_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_HPP

#include "../stream/row.hpp"
#include "../stream/variant.hpp"

namespace	Tesca
{
	class	Accessor
	{
		public:
			virtual	~Accessor ();

			virtual Stream::Variant	read (const Stream::Row&) const = 0;
	};
}

#endif

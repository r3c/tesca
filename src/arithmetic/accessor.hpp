
#ifndef __TESCA_ARITHMETIC_ACCESSOR_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_HPP

#include "../provision/row.hpp"
#include "../provision/variant.hpp"

namespace	Tesca
{
	class	Accessor
	{
		public:
			virtual	~Accessor ();

			virtual Provision::Variant	read (const Provision::Row&) const = 0;
	};
}

#endif

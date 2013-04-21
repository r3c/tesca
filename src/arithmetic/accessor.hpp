
#ifndef __TESCA_ARITHMETIC_ACCESSOR_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_HPP

#include "../provision/row.hpp"
#include "../storage/variant.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	Accessor
		{
			public:
				virtual	~Accessor ();

				virtual Storage::Variant	read (const Provision::Row&) const = 0;
		};
	}
}

#endif

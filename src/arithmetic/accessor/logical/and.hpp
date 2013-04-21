
#ifndef __TESCA_ARITHMETIC_ACCESSOR_LOGICAL_AND_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_LOGICAL_AND_HPP

#include "../logical.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	AndLogicalAccessor : public LogicalAccessor
		{
			public:
				AndLogicalAccessor (const Accessor*, const Accessor*);

				virtual Storage::Variant	read (const Provision::Row&) const;
		};
	}
}

#endif

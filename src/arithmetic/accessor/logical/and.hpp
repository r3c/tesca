
#ifndef __TESCA_ACCESSOR_LOGICAL_AND_HPP
#define __TESCA_ACCESSOR_LOGICAL_AND_HPP

#include "../logical.hpp"

namespace	Tesca
{
	class	AndLogicalAccessor : public LogicalAccessor
	{
		public:
			AndLogicalAccessor (const Accessor*, const Accessor*);

			virtual Variant	read (const Row&) const;
	};
}

#endif


#ifndef __TESCA_ARITHMETIC_ACCESSOR_LOGICAL_OR_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_LOGICAL_OR_HPP

#include "../logical.hpp"

namespace	Tesca
{
	class	OrLogicalAccessor : public LogicalAccessor
	{
		public:
			OrLogicalAccessor (const Accessor*, const Accessor*);

			virtual Stream::Variant	read (const Stream::Row&) const;
	};
}

#endif

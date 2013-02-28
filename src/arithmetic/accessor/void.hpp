
#ifndef __TESCA_ARITHMETIC_ACCESSOR_VOID_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_VOID_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	VoidAccessor : public Accessor
	{
		public:
			static const VoidAccessor	instance;

		protected:
			virtual Stream::Variant	read (const Stream::Row&) const;
	};
}

#endif

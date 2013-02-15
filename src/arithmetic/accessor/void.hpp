
#ifndef __TESCA_ACCESSOR_VOID_HPP
#define __TESCA_ACCESSOR_VOID_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	VoidAccessor : public Accessor
	{
		public:
			static const VoidAccessor	instance;

		protected:
			virtual Variant	read (const Row&) const;
	};
}

#endif

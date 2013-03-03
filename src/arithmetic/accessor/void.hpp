
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
			virtual Provision::Variant	read (const Provision::Row&) const;
	};
}

#endif

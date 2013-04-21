
#ifndef __TESCA_ARITHMETIC_ACCESSOR_VOID_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_VOID_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	VoidAccessor : public Accessor
		{
			public:
				static const VoidAccessor	instance;

			protected:
				virtual Storage::Variant	read (const Provision::Row&) const;
		};
	}
}

#endif

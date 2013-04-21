
#ifndef __TESCA_ARITHMETIC_ACCESSOR_CONSTANT_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_CONSTANT_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	ConstantAccessor : public Accessor
		{
			public:
				ConstantAccessor (const Storage::Variant&);

			protected:
				virtual Storage::Variant	read (const Provision::Row&) const;

			private:
				Storage::Variant	constant;
		};
	}
}

#endif

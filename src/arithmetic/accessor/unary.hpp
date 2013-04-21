
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	UnaryAccessor : public Accessor
		{
			public:
				UnaryAccessor (const Accessor*);

				virtual Storage::Variant	evaluate (const Storage::Variant&) const = 0;
				virtual Storage::Variant	read (const Provision::Row&) const;

			private:
				const Accessor*	source;
		};
	}
}

#endif


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

				virtual Provision::Variant	evaluate (const Provision::Variant&) const = 0;
				virtual Provision::Variant	read (const Provision::Row&) const;

			private:
				const Accessor*	source;
		};
	}
}

#endif

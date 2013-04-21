
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	BinaryAccessor : public Accessor
		{
			public:
				BinaryAccessor (const Accessor*, const Accessor*);

				virtual Storage::Variant	evaluate (const Storage::Variant&, const Storage::Variant&) const = 0;
				virtual Storage::Variant	read (const Provision::Row&) const;

			private:
				const Accessor*	lhs;
				const Accessor*	rhs;
		};
	}
}

#endif

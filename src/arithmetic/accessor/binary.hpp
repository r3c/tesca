
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	BinaryAccessor : public Accessor
	{
		public:
			BinaryAccessor (const Accessor*, const Accessor*);

			virtual Variant	evaluate (const Variant&, const Variant&) const = 0;
			virtual Variant	read (const Row&) const;

		private:
			const Accessor*	lhs;
			const Accessor*	rhs;
	};
}

#endif

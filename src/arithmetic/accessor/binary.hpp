
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	BinaryAccessor : public Accessor
	{
		public:
			BinaryAccessor (const Accessor*, const Accessor*);

			virtual Provision::Variant	evaluate (const Provision::Variant&, const Provision::Variant&) const = 0;
			virtual Provision::Variant	read (const Provision::Row&) const;

		private:
			const Accessor*	lhs;
			const Accessor*	rhs;
	};
}

#endif

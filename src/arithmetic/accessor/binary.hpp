
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	BinaryAccessor : public Accessor
	{
		public:
			BinaryAccessor (const Accessor*, const Accessor*);

			virtual Stream::Variant	evaluate (const Stream::Variant&, const Stream::Variant&) const = 0;
			virtual Stream::Variant	read (const Stream::Row&) const;

		private:
			const Accessor*	lhs;
			const Accessor*	rhs;
	};
}

#endif

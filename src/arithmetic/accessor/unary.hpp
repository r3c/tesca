
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	UnaryAccessor : public Accessor
	{
		public:
			UnaryAccessor (const Accessor*);

			virtual Variant	evaluate (const Variant&) const = 0;
			virtual Variant	read (const Row&) const;

		private:
			const Accessor*	source;
	};
}

#endif


#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	UnaryAccessor : public Accessor
	{
		public:
			UnaryAccessor (const Accessor*);

			virtual Stream::Variant	evaluate (const Stream::Variant&) const = 0;
			virtual Stream::Variant	read (const Stream::Row&) const;

		private:
			const Accessor*	source;
	};
}

#endif

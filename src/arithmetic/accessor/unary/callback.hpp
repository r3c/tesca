
#ifndef __TESCA_ACCESSOR_UNARY_CALLBACK_HPP
#define __TESCA_ACCESSOR_UNARY_CALLBACK_HPP

#include "../unary.hpp"

namespace	Tesca
{
	class	CallbackUnaryAccessor : public UnaryAccessor
	{
		public:
			typedef	Variant	(Callback) (const Variant&);

			CallbackUnaryAccessor (const Accessor*, const Callback*);

			virtual Variant	evaluate (const Variant&) const;

		private:
			Callback*	callback;
	};
}

#endif


#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_CALLBACK_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_CALLBACK_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	class	CallbackUnaryAccessor : public UnaryAccessor
	{
		public:
			typedef	std::function<Variant (const Variant&)>	Callback;

			CallbackUnaryAccessor (const Accessor*, Callback);

			virtual Variant	evaluate (const Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

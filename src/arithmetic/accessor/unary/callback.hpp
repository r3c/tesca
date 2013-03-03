
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_CALLBACK_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_CALLBACK_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	class	CallbackUnaryAccessor : public UnaryAccessor
	{
		public:
			typedef	std::function<Provision::Variant (const Provision::Variant&)>	Callback;

			CallbackUnaryAccessor (const Accessor*, Callback);

			virtual Provision::Variant	evaluate (const Provision::Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

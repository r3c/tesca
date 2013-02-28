
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_CALLBACK_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_CALLBACK_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	class	CallbackUnaryAccessor : public UnaryAccessor
	{
		public:
			typedef	std::function<Stream::Variant (const Stream::Variant&)>	Callback;

			CallbackUnaryAccessor (const Accessor*, Callback);

			virtual Stream::Variant	evaluate (const Stream::Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

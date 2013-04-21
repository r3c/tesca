
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_CALLBACK_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_CALLBACK_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	CallbackUnaryAccessor : public UnaryAccessor
		{
			public:
				typedef	std::function<Storage::Variant (const Storage::Variant&)>	Callback;

				CallbackUnaryAccessor (const Accessor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

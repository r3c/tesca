
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_NUMBER_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_NUMBER_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	NumberUnaryAccessor : public UnaryAccessor
		{
			public:
				typedef	std::function<Storage::Variant (Glay::Float64)>	Callback;

				NumberUnaryAccessor (const Accessor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

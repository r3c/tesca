
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_BOOLEAN_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_BOOLEAN_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	BooleanUnaryAccessor : public UnaryAccessor
		{
			public:
				typedef	std::function<Storage::Variant (bool)>	Callback;

				BooleanUnaryAccessor (const Accessor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

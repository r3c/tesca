
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_STRING_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_STRING_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	StringUnaryAccessor : public UnaryAccessor
		{
			public:
				typedef	std::function<Storage::Variant (const std::string&)>	Callback;

				StringUnaryAccessor (const Accessor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

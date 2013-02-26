
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_STRING_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_STRING_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	class	StringUnaryAccessor : public UnaryAccessor
	{
		public:
			typedef	std::function<Variant (std::string&)>	Callback;

			StringUnaryAccessor (const Accessor*, Callback);

			virtual Variant	evaluate (const Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

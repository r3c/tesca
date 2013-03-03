
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_STRING_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_STRING_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	class	StringUnaryAccessor : public UnaryAccessor
	{
		public:
			typedef	std::function<Provision::Variant (const std::string&)>	Callback;

			StringUnaryAccessor (const Accessor*, Callback);

			virtual Provision::Variant	evaluate (const Provision::Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

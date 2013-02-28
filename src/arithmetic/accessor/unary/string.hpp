
#ifndef __TESCA_ARITHMETIC_ACCESSOR_UNARY_STRING_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_UNARY_STRING_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	class	StringUnaryAccessor : public UnaryAccessor
	{
		public:
			typedef	std::function<Stream::Variant (const std::string&)>	Callback;

			StringUnaryAccessor (const Accessor*, Callback);

			virtual Stream::Variant	evaluate (const Stream::Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

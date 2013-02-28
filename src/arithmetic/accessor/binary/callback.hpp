
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_CALLBACK_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_CALLBACK_HPP

#include <functional>
#include "../binary.hpp"

namespace	Tesca
{
	class	CallbackBinaryAccessor : public BinaryAccessor
	{
		public:
			typedef	std::function<Stream::Variant (const Stream::Variant&, const Stream::Variant&)>	Callback;

			CallbackBinaryAccessor (const Accessor*, const Accessor*, Callback);

			virtual Stream::Variant	evaluate (const Stream::Variant&, const Stream::Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

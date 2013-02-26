
#ifndef __TESCA_ACCESSOR_BINARY_CALLBACK_HPP
#define __TESCA_ACCESSOR_BINARY_CALLBACK_HPP

#include <functional>
#include "../binary.hpp"

namespace	Tesca
{
	class	CallbackBinaryAccessor : public BinaryAccessor
	{
		public:
			typedef	std::function<Variant (const Variant&, const Variant&)>	Callback;

			CallbackBinaryAccessor (const Accessor*, const Accessor*, Callback);

			virtual Variant	evaluate (const Variant&, const Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

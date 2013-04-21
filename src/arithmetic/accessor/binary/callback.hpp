
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_CALLBACK_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_CALLBACK_HPP

#include <functional>
#include "../binary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	CallbackBinaryAccessor : public BinaryAccessor
		{
			public:
				typedef	std::function<Provision::Variant (const Provision::Variant&, const Provision::Variant&)>	Callback;

				CallbackBinaryAccessor (const Accessor*, const Accessor*, Callback);

				virtual Provision::Variant	evaluate (const Provision::Variant&, const Provision::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

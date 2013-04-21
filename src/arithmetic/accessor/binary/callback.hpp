
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
				typedef	std::function<Storage::Variant (const Storage::Variant&, const Storage::Variant&)>	Callback;

				CallbackBinaryAccessor (const Accessor*, const Accessor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&, const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

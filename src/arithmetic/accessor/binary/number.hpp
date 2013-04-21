
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_NUMBER_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_NUMBER_HPP

#include <functional>
#include "../../../../lib/glay/src/include.hpp"
#include "../binary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	NumberBinaryAccessor : public BinaryAccessor
		{
			public:
				typedef	std::function<Storage::Variant (Glay::Float64, Glay::Float64)>	Callback;

				NumberBinaryAccessor (const Accessor*, const Accessor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&, const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

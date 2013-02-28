
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_NUMBER_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_NUMBER_HPP

#include <functional>
#include "../../../glay/glay.hpp"
#include "../binary.hpp"

namespace	Tesca
{
	class	NumberBinaryAccessor : public BinaryAccessor
	{
		public:
			typedef	std::function<Stream::Variant (Glay::Float64, Glay::Float64)>	Callback;

			NumberBinaryAccessor (const Accessor*, const Accessor*, Callback);

			virtual Stream::Variant	evaluate (const Stream::Variant&, const Stream::Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

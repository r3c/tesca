
#ifndef __TESCA_ARITHMETIC_ACCESSOR_BINARY_NUMBER_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_BINARY_NUMBER_HPP

#include <functional>
#include "../../../../lib/glay/src/glay.hpp"
#include "../binary.hpp"

namespace	Tesca
{
	class	NumberBinaryAccessor : public BinaryAccessor
	{
		public:
			typedef	std::function<Provision::Variant (Glay::Float64, Glay::Float64)>	Callback;

			NumberBinaryAccessor (const Accessor*, const Accessor*, Callback);

			virtual Provision::Variant	evaluate (const Provision::Variant&, const Provision::Variant&) const;

		private:
			Callback	callback;
	};
}

#endif

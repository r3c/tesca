
#ifndef __TESCA_ACCESSOR_BINARY_NUMBER_HPP
#define __TESCA_ACCESSOR_BINARY_NUMBER_HPP

#include "../../../glay/glay.hpp"
#include "../binary.hpp"

namespace	Tesca
{
	class	NumberBinaryAccessor : public BinaryAccessor
	{
		public:
			typedef	Variant	(Callback) (Glay::Float64, Glay::Float64);

			NumberBinaryAccessor (const Accessor*, const Accessor*, const Callback*);

			virtual Variant	evaluate (const Variant&, const Variant&) const;

		private:
			Callback*	callback;
	};
}

#endif


#ifndef __TESCA_ACCESSOR_BINARY_CALLBACK_HPP
#define __TESCA_ACCESSOR_BINARY_CALLBACK_HPP

#include "../binary.hpp"

namespace	Tesca
{
	class	CallbackBinaryAccessor : public BinaryAccessor
	{
		public:
			typedef	Variant	(Callback) (const Variant&, const Variant&);

			CallbackBinaryAccessor (const Accessor*, const Accessor*, const Callback*);

			virtual Variant	evaluate (const Variant&, const Variant&) const;

		private:
			Callback*	callback;
	};
}

#endif

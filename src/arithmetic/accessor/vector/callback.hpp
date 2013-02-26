
#ifndef __TESCA_ACCESSOR_VECTOR_CALLBACK_HPP
#define __TESCA_ACCESSOR_VECTOR_CALLBACK_HPP

#include <functional>
#include "../vector.hpp"

namespace	Tesca
{
	class	CallbackVectorAccessor : public VectorAccessor
	{
		public:
			typedef	std::function<Variant (const Values&)>	Callback;

			CallbackVectorAccessor (const Accessors&, Callback);

			virtual Variant	evaluate (const Values&) const;

		private:
			Callback	callback;
	};
}

#endif

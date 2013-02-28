
#ifndef __TESCA_ARITHMETIC_ACCESSOR_VECTOR_CALLBACK_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_VECTOR_CALLBACK_HPP

#include <functional>
#include "../vector.hpp"

namespace	Tesca
{
	class	CallbackVectorAccessor : public VectorAccessor
	{
		public:
			typedef	std::function<Stream::Variant (const Stream::Variant*, Glay::Int32u)>	Callback;

			CallbackVectorAccessor (const std::vector<const Accessor*>&, Callback);

			virtual Stream::Variant	evaluate (const Stream::Variant*, Glay::Int32u) const;

		private:
			Callback	callback;
	};
}

#endif

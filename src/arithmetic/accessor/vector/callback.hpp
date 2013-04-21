
#ifndef __TESCA_ARITHMETIC_ACCESSOR_VECTOR_CALLBACK_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_VECTOR_CALLBACK_HPP

#include <functional>
#include "../vector.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	CallbackVectorAccessor : public VectorAccessor
		{
			public:
				typedef	std::function<Storage::Variant (const Storage::Variant*, Glay::Int32u)>	Callback;

				CallbackVectorAccessor (const std::vector<const Accessor*>&, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant*, Glay::Int32u) const;

			private:
				Callback	callback;
		};
	}
}

#endif

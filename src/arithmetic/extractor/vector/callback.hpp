
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_CALLBACK_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_CALLBACK_HPP

#include <functional>
#include "../vector.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	CallbackVectorExtractor : public VectorExtractor
		{
			public:
				typedef	std::function<Storage::Variant (const Storage::Variant*, Glay::Int32u)>	Callback;

				CallbackVectorExtractor (const std::vector<const Extractor*>&, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant*, Glay::Int32u) const;

			private:
				Callback	callback;
		};
	}
}

#endif

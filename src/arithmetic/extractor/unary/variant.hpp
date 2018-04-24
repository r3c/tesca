
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_UNARY_VARIANT_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_UNARY_VARIANT_HPP

#include <functional>
#include "../unary.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class VariantUnaryExtractor : public UnaryExtractor
		{
			public:
				typedef std::function<Storage::Variant (const Storage::Variant&)> Callback;

				VariantUnaryExtractor (const Extractor*, Callback);

				virtual Storage::Variant evaluate (const Storage::Variant&) const;

			private:
				Callback callback;
		};
	}
}

#endif

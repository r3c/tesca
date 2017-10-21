
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_BINARY_VARIANT_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_BINARY_VARIANT_HPP

#include <functional>
#include "../binary.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class VariantBinaryExtractor : public BinaryExtractor
		{
			public:
				typedef std::function<Storage::Variant (const Storage::Variant&, const Storage::Variant&)> Callback;

				VariantBinaryExtractor (const Extractor*, const Extractor*, Callback);

				virtual Storage::Variant evaluate (const Storage::Variant&, const Storage::Variant&) const;

			private:
				Callback callback;
		};
	}
}

#endif

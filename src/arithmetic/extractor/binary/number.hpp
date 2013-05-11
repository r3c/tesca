
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_BINARY_NUMBER_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_BINARY_NUMBER_HPP

#include <functional>
#include "../../../../lib/glay/src/include.hpp"
#include "../binary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	NumberBinaryExtractor : public BinaryExtractor
		{
			public:
				typedef	std::function<Storage::Variant (Glay::Float64, Glay::Float64)>	Callback;

				NumberBinaryExtractor (const Extractor*, const Extractor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&, const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

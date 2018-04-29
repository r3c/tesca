
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_UNARY_NUMBER_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_UNARY_NUMBER_HPP

#include <functional>
#include <string>
#include "../unary.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class NumberUnaryExtractor : public UnaryExtractor
		{
			public:
				typedef std::function<Storage::Variant (Glay::Float64)> Callback;

				NumberUnaryExtractor (const Extractor*, const std::string&, Callback);

				virtual Storage::Variant evaluate (const Storage::Variant&) const;

			private:
				Callback callback;
		};
	}
}

#endif

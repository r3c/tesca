
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_UNARY_BOOLEAN_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_UNARY_BOOLEAN_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	BooleanUnaryExtractor : public UnaryExtractor
		{
			public:
				typedef	std::function<Storage::Variant (bool)>	Callback;

				BooleanUnaryExtractor (const Extractor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

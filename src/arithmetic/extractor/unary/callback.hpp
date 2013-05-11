
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_UNARY_CALLBACK_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_UNARY_CALLBACK_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	CallbackUnaryExtractor : public UnaryExtractor
		{
			public:
				typedef	std::function<Storage::Variant (const Storage::Variant&)>	Callback;

				CallbackUnaryExtractor (const Extractor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

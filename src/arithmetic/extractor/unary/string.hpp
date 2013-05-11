
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_UNARY_STRING_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_UNARY_STRING_HPP

#include <functional>
#include "../unary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	StringUnaryExtractor : public UnaryExtractor
		{
			public:
				typedef	std::function<Storage::Variant (const std::string&)>	Callback;

				StringUnaryExtractor (const Extractor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

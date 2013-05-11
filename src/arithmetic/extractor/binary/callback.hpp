
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_BINARY_CALLBACK_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_BINARY_CALLBACK_HPP

#include <functional>
#include "../binary.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	CallbackBinaryExtractor : public BinaryExtractor
		{
			public:
				typedef	std::function<Storage::Variant (const Storage::Variant&, const Storage::Variant&)>	Callback;

				CallbackBinaryExtractor (const Extractor*, const Extractor*, Callback);

				virtual Storage::Variant	evaluate (const Storage::Variant&, const Storage::Variant&) const;

			private:
				Callback	callback;
		};
	}
}

#endif

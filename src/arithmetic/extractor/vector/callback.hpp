
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_CALLBACK_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_CALLBACK_HPP

#include <functional>
#include <string>
#include "../vector.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class CallbackVectorExtractor : public VectorExtractor
		{
			public:
				typedef std::function<Storage::Variant (const Storage::Variant*, Glay::Int32u)> Callback;

				CallbackVectorExtractor (const std::vector<const Extractor*>&, const std::string&, Callback);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const* const) const;
				virtual Storage::Variant extract (const Provision::Row&) const;

			private:
				Callback callback;
				std::string name;
		};
	}
}

#endif

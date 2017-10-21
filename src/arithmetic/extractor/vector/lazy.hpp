
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_LAZY_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_LAZY_HPP

#include <functional>
#include "../vector.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class LazyVectorExtractor : public VectorExtractor
		{
			public:
				typedef std::function<Storage::Variant (Glay::Int32u)> Resolver;
				typedef std::function<Storage::Variant (Resolver, Glay::Int32u)> Callback;

				LazyVectorExtractor (const std::vector<const Extractor*>&, Callback);

				virtual Storage::Variant compute (const Aggregator* const*) const;
				virtual Storage::Variant extract (const Provision::Row&) const;

			private:
				Callback callback;
		};
	}
}

#endif

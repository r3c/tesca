
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_LAZY_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_LAZY_HPP

#include <functional>
#include <string>
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

				LazyVectorExtractor (const std::vector<Extractor const*>&, const std::string&, Callback);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const*) const;
				virtual Storage::Variant extract (Provision::Row const&) const;

			private:
				Callback callback;
				std::string name;
		};
	}
}

#endif

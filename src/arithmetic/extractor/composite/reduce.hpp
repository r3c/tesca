
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_COMPOSITE_REDUCE_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_COMPOSITE_REDUCE_HPP

#include <string>
#include "../composite.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		template<typename T>
		class ReduceCompositeExtractor : public CompositeExtractor
		{
			public:
				ReduceCompositeExtractor (Glay::Int32u, Extractor const*, const std::string&);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const*) const;
				virtual void prepare (Aggregator**) const;
				virtual void update (Aggregator* const*, Provision::Row const&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				Extractor const* operand;
				const std::string prefix;
				Glay::Int32u slot;
		};
	}
}

#include "reduce.hxx"

#endif

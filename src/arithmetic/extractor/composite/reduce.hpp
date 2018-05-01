
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
				ReduceCompositeExtractor (Glay::Int32u, const Extractor*, const std::string&);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const* const) const;
				virtual void prepare (Aggregator** const) const;
				virtual void update (Aggregator** const, const Provision::Row&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				const Extractor* operand;
				const std::string prefix;
				Glay::Int32u slot;
		};
	}
}

#include "reduce.hxx"

#endif

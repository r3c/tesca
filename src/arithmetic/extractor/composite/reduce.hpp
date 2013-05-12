
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_COMPOSITE_REDUCE_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_COMPOSITE_REDUCE_HPP

#include "../composite.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		template<typename T>
		class	ReduceCompositeExtractor : public CompositeExtractor
		{
			public:
				ReduceCompositeExtractor (Glay::Int32u, const Extractor*);

				virtual Storage::Variant	compute (const Aggregator* const*) const;
				virtual void				populate (Aggregator**) const;
				virtual void				store (Aggregator**, const Provision::Row&) const;

			protected:
				virtual void	recurse (RecurseCallback) const;

			private:
				const Extractor*	operand;
				Glay::Int32u		slot;
		};
	}
}

#include "reduce.hxx"

#endif

#ifndef __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_HPP

#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class LogicalExtractor : public Extractor
		{
			public:
				LogicalExtractor (const Extractor*, const Extractor*);

			protected:
				bool collectLHS (Aggregator const* const* const) const;
				bool collectRHS (Aggregator const* const* const) const;

				bool extractLHS (const Provision::Row&) const;
				bool extractRHS (const Provision::Row&) const;

				virtual void recurse (RecurseCallback) const;

				const Extractor* lhs;
				const Extractor* rhs;
		};
	}
}

#endif

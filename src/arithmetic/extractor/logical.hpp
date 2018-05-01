
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
				LogicalExtractor (Extractor const*, Extractor const*);

			protected:
				bool collectLHS (Aggregator const* const*) const;
				bool collectRHS (Aggregator const* const*) const;

				bool extractLHS (Provision::Row const&) const;
				bool extractRHS (Provision::Row const&) const;

				virtual void recurse (RecurseCallback) const;

				Extractor const* lhs;
				Extractor const* rhs;
		};
	}
}

#endif

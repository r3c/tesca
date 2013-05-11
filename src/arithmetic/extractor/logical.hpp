
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_HPP

#include "../extractor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	LogicalExtractor : public Extractor
		{
			public:
				LogicalExtractor (const Extractor*, const Extractor*);

			protected:
				bool	computeLHS (const Aggregator* const*) const;
				bool	computeRHS (const Aggregator* const*) const;

				bool	extractLHS (const Provision::Row&) const;
				bool	extractRHS (const Provision::Row&) const;

				virtual void	recurse (RecurseCallback) const;

			private:
				const Extractor*	lhs;
				const Extractor*	rhs;
		};
	}
}

#endif

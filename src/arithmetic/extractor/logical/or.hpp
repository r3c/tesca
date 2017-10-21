
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_OR_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_OR_HPP

#include "../logical.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class OrLogicalExtractor : public LogicalExtractor
		{
			public:
				OrLogicalExtractor (const Extractor*, const Extractor*);

				virtual Storage::Variant compute (const Aggregator* const*) const;
				virtual Storage::Variant extract (const Provision::Row&) const;
		};
	}
}

#endif

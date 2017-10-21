
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_AND_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_AND_HPP

#include "../logical.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class AndLogicalExtractor : public LogicalExtractor
		{
			public:
				AndLogicalExtractor (const Extractor*, const Extractor*);

				virtual Storage::Variant compute (const Aggregator* const*) const;
				virtual Storage::Variant extract (const Provision::Row&) const;
		};
	}
}

#endif

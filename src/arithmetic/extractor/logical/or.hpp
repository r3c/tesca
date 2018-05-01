
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_OR_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_OR_HPP

#include <string>
#include "../logical.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class OrLogicalExtractor : public LogicalExtractor
		{
			public:
				OrLogicalExtractor (const Extractor*, const Extractor*);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const* const) const;
				virtual Storage::Variant extract (const Provision::Row&) const;
		};
	}
}

#endif

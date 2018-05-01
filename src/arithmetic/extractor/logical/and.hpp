
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_AND_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_LOGICAL_AND_HPP

#include <string>
#include "../logical.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class AndLogicalExtractor : public LogicalExtractor
		{
			public:
				AndLogicalExtractor (Extractor const*, Extractor const*);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const*) const;
				virtual Storage::Variant extract (Provision::Row const&) const;
		};
	}
}

#endif

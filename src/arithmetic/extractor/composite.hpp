
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_COMPOSITE_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_COMPOSITE_HPP

#include <functional>
#include "../../../lib/glay/src/glay.hpp"
#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class CompositeExtractor : public Extractor
		{
			public:
				virtual Glay::Int32u getFlags () const;

				virtual Storage::Variant extract (Provision::Row const&) const;
		};
	}
}

#endif

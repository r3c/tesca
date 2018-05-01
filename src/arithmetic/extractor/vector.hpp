
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_HPP

#include <vector>
#include "../../../lib/glay/src/glay.hpp"
#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class VectorExtractor : public Extractor
		{
			public:
				VectorExtractor (const std::vector<Extractor const*>&);
				virtual ~VectorExtractor ();

			protected:
				virtual void recurse (RecurseCallback) const;

				Extractor const** extractors;
				Glay::Int32u length;
		};
	}
}

#endif

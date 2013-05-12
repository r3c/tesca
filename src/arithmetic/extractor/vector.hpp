
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_VECTOR_HPP

#include <vector>
#include "../../../lib/glay/src/include.hpp"
#include "../extractor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	VectorExtractor : public Extractor
		{
			public:
				VectorExtractor (const std::vector<const Extractor*>&);
				virtual	~VectorExtractor ();

			protected:
				virtual void	recurse (RecurseCallback) const;

				const Extractor**	extractors;
				Glay::Int32u		length;
		};
	}
}

#endif

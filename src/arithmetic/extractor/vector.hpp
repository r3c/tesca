
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

				virtual Storage::Variant	compute (const Aggregator* const*) const;
				virtual Storage::Variant	extract (const Provision::Row&) const;

			protected:
				virtual Storage::Variant	evaluate (const Storage::Variant*, Glay::Int32u) const = 0;
				virtual void				recurse (RecurseCallback) const;

			private:
				const Extractor**	extractors;
				Glay::Int32u		length;
		};
	}
}

#endif

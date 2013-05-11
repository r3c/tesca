
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_BINARY_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_BINARY_HPP

#include "../extractor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	BinaryExtractor : public Extractor
		{
			public:
				BinaryExtractor (const Extractor*, const Extractor*);

				virtual Storage::Variant	compute (const Aggregator* const*) const;
				virtual Storage::Variant	extract (const Provision::Row&) const;

			protected:
				virtual Storage::Variant	evaluate (const Storage::Variant&, const Storage::Variant&) const = 0;
				virtual void				recurse (RecurseCallback) const;

			private:
				const Extractor*	lhs;
				const Extractor*	rhs;
		};
	}
}

#endif


#ifndef __TESCA_ARITHMETIC_EXTRACTOR_CONSTANT_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_CONSTANT_HPP

#include "../extractor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	ConstantExtractor : public Extractor
		{
			public:
				ConstantExtractor (const Storage::Variant&);

				virtual Glay::Int32u	getFlags () const;

				virtual Storage::Variant	compute (const Aggregator* const*) const;
				virtual Storage::Variant	extract (const Provision::Row&) const;

			private:
				Storage::Variant	value;
		};
	}
}

#endif

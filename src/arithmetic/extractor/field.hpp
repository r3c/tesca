
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_FIELD_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_FIELD_HPP

#include <string>
#include "../../../lib/glay/src/include.hpp"
#include "../extractor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	FieldExtractor : public Extractor
		{
			public:
				FieldExtractor (Glay::Int32u);

				virtual Glay::Int32u	getFlags () const;

				virtual Storage::Variant	compute (const Aggregator* const*) const;
				virtual Storage::Variant	extract (const Provision::Row&) const;

			private:
				Glay::Int32u	field;
		};
	}
}

#endif

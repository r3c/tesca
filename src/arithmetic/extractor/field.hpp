
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_FIELD_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_FIELD_HPP

#include <string>
#include "../../../lib/glay/src/glay.hpp"
#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class FieldExtractor : public Extractor
		{
			public:
				FieldExtractor (Glay::Int32u, const std::string&);

				virtual std::string createName (Glay::Int32u) const;

				virtual Glay::Int32u getFlags () const;

				virtual Storage::Variant compute (const Aggregator* const*) const;
				virtual Storage::Variant extract (const Provision::Row&) const;

			private:
				Glay::Int32u field;
				std::string name;
		};
	}
}

#endif

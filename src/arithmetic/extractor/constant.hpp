
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_CONSTANT_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_CONSTANT_HPP

#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class ConstantExtractor : public Extractor
		{
			public:
				ConstantExtractor (Storage::Variant const&);

				virtual std::string createName (Glay::Int32u) const;

				virtual Glay::Int32u getFlags () const;

				virtual Storage::Variant collect (Aggregator const* const*) const;
				virtual Storage::Variant extract (Provision::Row const&) const;

			private:
				Storage::Variant value;
		};
	}
}

#endif

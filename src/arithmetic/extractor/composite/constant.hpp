
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_COMPOSITE_CONSTANT_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_COMPOSITE_CONSTANT_HPP

#include <string>
#include "../composite.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		template<typename T>
		class ConstantCompositeExtractor : public CompositeExtractor
		{
			public:
				ConstantCompositeExtractor (Glay::Int32u, const Storage::Variant&, const std::string&);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant compute (const Aggregator* const*) const;
				virtual void populate (Aggregator**) const;
				virtual void store (Aggregator**, const Provision::Row&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				std::string name;
				Glay::Int32u slot;
				Storage::Variant value;
		};
	}
}

#include "constant.hxx"

#endif

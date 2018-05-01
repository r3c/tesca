
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
				ConstantCompositeExtractor (Glay::Int32u, Storage::Variant const&, const std::string&);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const*) const;
				virtual void prepare (Aggregator**) const;
				virtual void update (Aggregator* const*, Provision::Row const&) const;

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

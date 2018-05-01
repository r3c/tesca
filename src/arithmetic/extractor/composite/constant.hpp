
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

				virtual Storage::Variant collect (Aggregator const* const* const) const;
				virtual void prepare (Aggregator** const) const;
				virtual void update (Aggregator** const, const Provision::Row&) const;

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

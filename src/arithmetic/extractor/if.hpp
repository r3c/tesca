
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_IF_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_IF_HPP

#include <string>
#include "../extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class IfExtractor : public Extractor
		{
			public:
				IfExtractor (Extractor const*, Extractor const*, Extractor const*);
				IfExtractor (Extractor const*, Extractor const*);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant collect (Aggregator const* const*) const;
				virtual Storage::Variant extract (Provision::Row const&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				Extractor const* condition;
				Extractor const* onFalse;
				Extractor const* onTrue;
		};
	}
}

#endif

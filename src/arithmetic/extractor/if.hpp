
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
				IfExtractor (const Extractor*, const Extractor*, const Extractor*);
				IfExtractor (const Extractor*, const Extractor*);

				virtual std::string createName (Glay::Int32u) const;

				virtual Storage::Variant compute (const Aggregator* const*) const;
				virtual Storage::Variant extract (const Provision::Row&) const;

			protected:
				virtual void recurse (RecurseCallback) const;

			private:
				const Extractor* condition;
				const Extractor* onFalse;
				const Extractor* onTrue;
		};
	}
}

#endif

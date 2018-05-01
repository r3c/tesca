
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_HPP

#include <string>
#include "../provision/row.hpp"
#include "../storage/variant.hpp"
#include "aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class Extractor
		{
			public:
				enum Flags
				{
					COMPOSITE = 1 << 0,
					SCALAR = 1 << 1
				};

				virtual ~Extractor ();

				virtual std::string createName (Glay::Int32u) const = 0;

				virtual Glay::Int32u getFlags () const;

				// Row methods
				virtual Storage::Variant extract (const Provision::Row&) const = 0;

				// Aggregation methods
				virtual Storage::Variant collect (Aggregator const* const* const) const = 0;
				virtual void prepare (Aggregator** const) const;
				virtual void update (Aggregator** const, const Provision::Row&) const;

			protected:
				typedef std::function<void (const Extractor*)> RecurseCallback;

				virtual void recurse (RecurseCallback) const;
		};
	}
}

#endif

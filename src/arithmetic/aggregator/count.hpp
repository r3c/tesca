
#ifndef __TESCA_AGGREGATOR_COUNT_HPP
#define __TESCA_AGGREGATOR_COUNT_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class CountAggregator : public Aggregator
		{
			public:
				CountAggregator ();

				virtual Storage::Variant collect () const;
				virtual bool update (Storage::Variant const&);

			private:
				Glay::Int64u count;
		};
	}
}

#endif

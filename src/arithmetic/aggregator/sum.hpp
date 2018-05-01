
#ifndef __TESCA_AGGREGATOR_SUM_HPP
#define __TESCA_AGGREGATOR_SUM_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class SumAggregator : public Aggregator
		{
			public:
				SumAggregator ();

				virtual Storage::Variant collect () const;
				virtual void reset ();
				virtual bool update (const Storage::Variant&);

			private:
				Glay::Float64 sum;
		};
	}
}

#endif

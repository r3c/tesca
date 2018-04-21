
#ifndef __TESCA_AGGREGATOR_VARIANCE_HPP
#define __TESCA_AGGREGATOR_VARIANCE_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class VarianceAggregator : public Aggregator
		{
			public:
				VarianceAggregator ();

				virtual Storage::Variant compute () const;
				virtual bool push (const Storage::Variant&);
				virtual void reset ();

			private:
				Glay::Int32u count;
				Glay::Float64 mean;
				Glay::Float64 sum;
		};
	}
}

#endif

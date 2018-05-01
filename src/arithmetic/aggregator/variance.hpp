
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

				virtual Storage::Variant collect () const;
				virtual bool update (Storage::Variant const&);

			private:
				Glay::Int64u count;
				Glay::Float64 mean;
				Glay::Float64 sum;
		};
	}
}

#endif

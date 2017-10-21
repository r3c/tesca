
#ifndef __TESCA_AGGREGATOR_AVERAGE_HPP
#define __TESCA_AGGREGATOR_AVERAGE_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class AverageAggregator : public Aggregator
		{
			public:
				AverageAggregator ();

				virtual Storage::Variant compute () const;
				virtual bool push (const Storage::Variant&);
				virtual void reset ();

			private:
				Glay::Int32u count;
				Glay::Float64 sum;
		};
	}
}

#endif

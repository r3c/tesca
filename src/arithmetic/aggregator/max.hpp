
#ifndef __TESCA_AGGREGATOR_MAX_HPP
#define __TESCA_AGGREGATOR_MAX_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class MaxAggregator : public Aggregator
		{
			public:
				MaxAggregator ();

				virtual Storage::Variant compute () const;
				virtual bool push (const Storage::Variant&);
				virtual void reset ();

			private:
				bool empty;
				Glay::Float64 max;
		};
	}
}

#endif

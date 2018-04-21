
#ifndef __TESCA_AGGREGATOR_MIN_HPP
#define __TESCA_AGGREGATOR_MIN_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class MinAggregator : public Aggregator
		{
			public:
				MinAggregator ();

				virtual Storage::Variant compute () const;
				virtual bool push (const Storage::Variant&);
				virtual void reset ();

			private:
				bool empty;
				Glay::Float64 min;
		};
	}
}

#endif

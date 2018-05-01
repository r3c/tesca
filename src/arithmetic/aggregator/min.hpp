
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

				virtual Storage::Variant collect () const;
				virtual bool update (Storage::Variant const&);

			private:
				bool empty;
				Glay::Float64 min;
		};
	}
}

#endif


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

				virtual Storage::Variant compute () const;
				virtual bool push (const Storage::Variant&);
				virtual void reset ();

			private:
				Glay::Int32u count;
		};
	}
}

#endif

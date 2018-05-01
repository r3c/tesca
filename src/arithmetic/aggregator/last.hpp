
#ifndef __TESCA_AGGREGATOR_LAST_HPP
#define __TESCA_AGGREGATOR_LAST_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class LastAggregator : public Aggregator
		{
			public:
				LastAggregator ();

				virtual Storage::Variant collect () const;
				virtual void reset ();
				virtual bool update (const Storage::Variant&);

			private:
				Storage::Variant last;
		};
	}
}

#endif

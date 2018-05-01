
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
				virtual bool update (Storage::Variant const&);

			private:
				Storage::Variant last;
		};
	}
}

#endif

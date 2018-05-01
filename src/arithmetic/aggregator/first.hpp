
#ifndef __TESCA_AGGREGATOR_FIRST_HPP
#define __TESCA_AGGREGATOR_FIRST_HPP

#include "../../../lib/glay/src/glay.hpp"
#include "../aggregator.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class FirstAggregator : public Aggregator
		{
			public:
				FirstAggregator ();

				virtual Storage::Variant collect () const;
				virtual bool update (Storage::Variant const&);

			private:
				bool empty;
				Storage::Variant first;
		};
	}
}

#endif

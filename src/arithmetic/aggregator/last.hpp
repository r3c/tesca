
#ifndef __TESCA_AGGREGATOR_LAST_HPP
#define __TESCA_AGGREGATOR_LAST_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../aggregator.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	LastAggregator : public Aggregator
		{
			public:
				LastAggregator ();

				virtual Storage::Variant	compute () const;
				virtual bool				push (const Storage::Variant&);
				virtual void				reset ();

			private:
				Storage::Variant	last;
		};
	}
}

#endif

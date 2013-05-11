
#ifndef __TESCA_AGGREGATOR_SUM_HPP
#define __TESCA_AGGREGATOR_SUM_HPP

#include "../../../lib/glay/src/include.hpp"
#include "../aggregator.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	SumAggregator : public Aggregator
		{
			public:
				SumAggregator ();

				virtual Storage::Variant	compute () const;
				virtual bool				push (const Storage::Variant&);
				virtual void				reset ();

			private:
				Glay::Float64	sum;
		};
	}
}

#endif

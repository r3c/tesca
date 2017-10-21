
#ifndef __TESCA_ARITHMETIC_AGGREGATOR_HPP
#define __TESCA_ARITHMETIC_AGGREGATOR_HPP

#include "../storage/variant.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class Aggregator
		{
			public:
				Aggregator (const Aggregator&);
				Aggregator ();
				virtual ~Aggregator ();

				Aggregator& operator = (const Aggregator&);

				virtual Storage::Variant compute () const = 0;
				virtual bool push (const Storage::Variant&) = 0;
				virtual void reset () = 0;
		};
	}
}

#endif

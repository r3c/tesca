
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
				Aggregator (Aggregator const&);
				Aggregator ();
				virtual ~Aggregator ();

				Aggregator& operator = (Aggregator const&);

				virtual Storage::Variant collect () const = 0;
				virtual bool update (Storage::Variant const&) = 0;
		};
	}
}

#endif


#ifndef __TESCA_ARITHMETIC_EXTRACTOR_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_HPP

#include "../provision/row.hpp"
#include "../storage/variant.hpp"
#include "aggregator.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	Extractor
		{
			public:
				virtual	~Extractor ();

				virtual bool				composite () const;
				virtual Storage::Variant	compute (const Aggregator* const*) const = 0;
				virtual Storage::Variant	extract (const Provision::Row&) const = 0;
				virtual void				populate (Aggregator**) const;
				virtual void				store (Aggregator**, const Provision::Row&) const;

			protected:
				typedef std::function<void (const Extractor*)>	RecurseCallback;

				virtual void	recurse (RecurseCallback) const;
		};
	}
}

#endif

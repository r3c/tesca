
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_SLOT_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_SLOT_HPP

#include <functional>
#include "../../../lib/glay/src/include.hpp"
#include "../extractor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	SlotExtractor : public Extractor
		{
			public:
				virtual Glay::Int32u	getFlags () const;

				virtual Storage::Variant	compute (const Aggregator* const*) const;
				virtual Storage::Variant	extract (const Provision::Row&) const;
				virtual void				populate (Aggregator**) const;
				virtual void				store (Aggregator**, const Provision::Row&) const;

			protected:
				SlotExtractor (Glay::Int32u);

				virtual Aggregator*			allocate () const = 0;
				virtual Storage::Variant	read (const Provision::Row&) const = 0;

			private:
				Glay::Int32u	slot;
		};
	}
}

#endif

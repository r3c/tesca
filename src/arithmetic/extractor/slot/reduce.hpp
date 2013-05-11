
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_SLOT_REDUCE_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_SLOT_REDUCE_HPP

#include "../slot.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		template<typename T>
		class	ReduceSlotExtractor : public SlotExtractor
		{
			public:
				ReduceSlotExtractor (Glay::Int32u, const Extractor*);

			protected:
				virtual Aggregator*			allocate () const;
				virtual Storage::Variant	read (const Provision::Row&) const;
				virtual void				recurse (RecurseCallback) const;

			private:
				const Extractor*	operand;
		};
	}
}

#include "reduce.hxx"

#endif

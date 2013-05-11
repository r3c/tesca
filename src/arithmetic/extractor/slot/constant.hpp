
#ifndef __TESCA_ARITHMETIC_EXTRACTOR_SLOT_CONSTANT_HPP
#define __TESCA_ARITHMETIC_EXTRACTOR_SLOT_CONSTANT_HPP

#include "../slot.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		template<typename T>
		class	ConstantSlotExtractor : public SlotExtractor
		{
			public:
				ConstantSlotExtractor (Glay::Int32u, const Storage::Variant&);

			protected:
				virtual Aggregator*			allocate () const;
				virtual Storage::Variant	read (const Provision::Row&) const;
				virtual void				recurse (RecurseCallback) const;

			private:
				Storage::Variant	value;
		};
	}
}

#include "constant.hxx"

#endif

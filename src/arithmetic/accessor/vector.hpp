
#ifndef __TESCA_ACCESSOR_VECTOR_HPP
#define __TESCA_ACCESSOR_VECTOR_HPP

#include <vector>
#include "../accessor.hpp"

namespace	Tesca
{
	class	VectorAccessor : public Accessor
	{
		public:
			typedef std::vector<const Accessor*>	Accessors;
			typedef std::vector<Variant>			Values;

			VectorAccessor (const Accessors&);

			virtual Variant	evaluate (const Values&) const = 0;
			virtual Variant	read (const Row&) const;

		private:
			Accessors	accessors;
	};
}

#endif

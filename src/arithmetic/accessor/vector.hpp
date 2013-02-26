
#ifndef __TESCA_ARITHMETIC_ACCESSOR_VECTOR_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_VECTOR_HPP

#include <vector>
#include "../../glay/glay.hpp"
#include "../accessor.hpp"

namespace	Tesca
{
	class	VectorAccessor : public Accessor
	{
		public:
					VectorAccessor (const std::vector<const Accessor*>&);
			virtual	~VectorAccessor ();

			virtual Variant	evaluate (const Variant*, Glay::Int32u) const = 0;
			virtual Variant	read (const Row&) const;

		private:
			const Accessor**	accessors;
			Glay::Int32u		length;
	};
}

#endif

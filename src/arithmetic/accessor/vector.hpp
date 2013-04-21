
#ifndef __TESCA_ARITHMETIC_ACCESSOR_VECTOR_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_VECTOR_HPP

#include <vector>
#include "../../../lib/glay/src/include.hpp"
#include "../accessor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	VectorAccessor : public Accessor
		{
			public:
						VectorAccessor (const std::vector<const Accessor*>&);
				virtual	~VectorAccessor ();

				virtual Provision::Variant	evaluate (const Provision::Variant*, Glay::Int32u) const = 0;
				virtual Provision::Variant	read (const Provision::Row&) const;

			private:
				const Accessor**	accessors;
				Glay::Int32u		length;
		};
	}
}

#endif

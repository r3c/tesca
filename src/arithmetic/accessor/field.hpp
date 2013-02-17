
#ifndef __TESCA_ACCESSOR_FIELD_HPP
#define __TESCA_ACCESSOR_FIELD_HPP

#include <string>
#include "../../glay/glay.hpp"
#include "../accessor.hpp"

namespace	Tesca
{
	class	FieldAccessor : public Accessor
	{
		public:
			FieldAccessor (Glay::Int32u);

		protected:
			virtual Variant	read (const Row&) const;

		private:
			Glay::Int32u	key;
	};
}

#endif

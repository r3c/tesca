
#ifndef __TESCA_ARITHMETIC_ACCESSOR_FIELD_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_FIELD_HPP

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
			virtual Provision::Variant	read (const Provision::Row&) const;

		private:
			Glay::Int32u	key;
	};
}

#endif

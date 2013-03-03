
#ifndef __TESCA_ARITHMETIC_ACCESSOR_CONSTANT_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_CONSTANT_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	ConstantAccessor : public Accessor
	{
		public:
			ConstantAccessor (const Provision::Variant&);

		protected:
			virtual Provision::Variant	read (const Provision::Row&) const;

		private:
			Provision::Variant	constant;
	};
}

#endif

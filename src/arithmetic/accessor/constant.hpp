
#ifndef __TESCA_ACCESSOR_CONSTANT_HPP
#define __TESCA_ACCESSOR_CONSTANT_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	ConstantAccessor : public Accessor
	{
		public:
			ConstantAccessor (const Variant&);

		protected:
			virtual Variant	read (const Row&) const;

		private:
			Variant	constant;
	};
}

#endif

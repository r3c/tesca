
#ifndef __TESCA_ARITHMETIC_ACCESSOR_CONSTANT_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_CONSTANT_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	ConstantAccessor : public Accessor
	{
		public:
			ConstantAccessor (const Stream::Variant&);

		protected:
			virtual Stream::Variant	read (const Stream::Row&) const;

		private:
			Stream::Variant	constant;
	};
}

#endif

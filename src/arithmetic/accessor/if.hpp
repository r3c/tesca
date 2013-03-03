
#ifndef __TESCA_ARITHMETIC_ACCESSOR_IF_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_IF_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	IfAccessor : public Accessor
	{
		public:
			IfAccessor (const Accessor*, const Accessor*, const Accessor*);
			IfAccessor (const Accessor*, const Accessor*);

		protected:
			virtual Provision::Variant	read (const Provision::Row&) const;

		private:
			const Accessor*	condition;
			const Accessor*	onFalse;
			const Accessor*	onTrue;
	};
}

#endif

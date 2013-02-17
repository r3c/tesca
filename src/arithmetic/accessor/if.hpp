
#ifndef __TESCA_ACCESSOR_IF_HPP
#define __TESCA_ACCESSOR_IF_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	IfAccessor : public Accessor
	{
		public:
			IfAccessor (const Accessor*, const Accessor*, const Accessor*);
			IfAccessor (const Accessor*, const Accessor*);

		protected:
			virtual Variant	read (const Row&) const;

		private:
			const Accessor*	condition;
			const Accessor*	onFalse;
			const Accessor*	onTrue;
	};
}

#endif

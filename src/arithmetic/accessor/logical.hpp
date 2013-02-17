
#ifndef __TESCA_ACCESSOR_LOGICAL_HPP
#define __TESCA_ACCESSOR_LOGICAL_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	LogicalAccessor : public Accessor
	{
		public:
			LogicalAccessor (const Accessor*, const Accessor*);

		protected:
			bool	testLHS (const Row&) const;
			bool	testRHS (const Row&) const;

		private:
			const Accessor*	lhs;
			const Accessor*	rhs;
	};
}

#endif


#ifndef __TESCA_ARITHMETIC_ACCESSOR_LOGICAL_HPP
#define __TESCA_ARITHMETIC_ACCESSOR_LOGICAL_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	LogicalAccessor : public Accessor
	{
		public:
			LogicalAccessor (const Accessor*, const Accessor*);

		protected:
			bool	testLHS (const Stream::Row&) const;
			bool	testRHS (const Stream::Row&) const;

		private:
			const Accessor*	lhs;
			const Accessor*	rhs;
	};
}

#endif

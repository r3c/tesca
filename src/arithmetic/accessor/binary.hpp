
#ifndef __TESCA_ACCESSOR_BINARY_HPP
#define __TESCA_ACCESSOR_BINARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	BinaryAccessor : public Accessor
	{
		public:
			typedef	Variant	(Evaluator) (const Variant&, const Variant&);

			/**/	BinaryAccessor (const Accessor*, const Accessor*, const Evaluator*);

			virtual Variant	read (const Row&) const;

		private:
			const Evaluator*	evaluator;
			const Accessor*		lhs;
			const Accessor*		rhs;
	};
}

#endif

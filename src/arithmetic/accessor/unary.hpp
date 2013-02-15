
#ifndef __TESCA_ACCESSOR_UNARY_HPP
#define __TESCA_ACCESSOR_UNARY_HPP

#include "../accessor.hpp"

namespace	Tesca
{
	class	UnaryAccessor : public Accessor
	{
		public:
			typedef	Variant	(Evaluator) (const Variant&);

			/**/	UnaryAccessor (const Accessor*, const Evaluator*);

			virtual Variant	read (const Row&) const;

		private:
			const Evaluator*	evaluator;
			const Accessor*		source;
	};
}

#endif


#ifndef __TESCA_READER_UNARY_HPP
#define __TESCA_READER_UNARY_HPP

#include "../reader.hpp"

namespace	Tesca
{
	class	UnaryReader : public Reader
	{
		public:
			typedef	Variant	(Evaluator) (const Variant&);

			/**/	UnaryReader (const Reader*,const Evaluator*);

			virtual Variant	read (const Row&) const;

		private:
			const Evaluator*	evaluator;
			const Reader*		source;
	};
}

#endif

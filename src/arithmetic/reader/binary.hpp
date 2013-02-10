
#ifndef __TESCA_READER_BINARY_HPP
#define __TESCA_READER_BINARY_HPP

#include "../reader.hpp"

namespace	Tesca
{
	class	BinaryReader : public Reader
	{
		public:
			typedef	Variant	(Evaluator) (const Variant&, const Variant&);

			/**/	BinaryReader (const Reader*, const Reader*, const Evaluator*);

			virtual Variant	read (const Row&) const;

		private:
			const Evaluator*	evaluator;
			const Reader*		lhs;
			const Reader*		rhs;
	};
}

#endif


#ifndef __TESCA_COLUMN_SUM_HPP
#define __TESCA_COLUMN_SUM_HPP

#include "aggregate.hpp"

namespace	Tesca
{
	class	SumColumn : public AggregateColumn
	{
		public:
			/**/			SumColumn (Column*);

			virtual Slot*	create () const;
	};
}

#endif

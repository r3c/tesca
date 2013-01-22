
#ifndef __TESCA_COLUMN_AVERAGE_HPP
#define __TESCA_COLUMN_AVERAGE_HPP

#include "aggregate.hpp"

namespace	Tesca
{
	class	AverageColumn : public AggregateColumn
	{
		public:
			/**/			AverageColumn (Column*);

			virtual Slot*	create () const;
	};
}

#endif

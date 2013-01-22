
#ifndef __TESCA_COLUMN_AGGREGATE_HPP
#define __TESCA_COLUMN_AGGREGATE_HPP

#include "map.hpp"

namespace	Tesca
{
	class	AggregateColumn : public MapColumn
	{
		public:
			/**/					AggregateColumn (Column*);

			virtual Slot*			create () const = 0;
			virtual const Value&	key () const;

		protected:
			virtual const Value&	map (const Value&);
	};
}

#endif

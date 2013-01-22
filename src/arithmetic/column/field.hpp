
#ifndef __TESCA_COLUMN_FIELD_HPP
#define __TESCA_COLUMN_FIELD_HPP

#include "value.hpp"

namespace	Tesca
{
	class	FieldColumn : public ValueColumn
	{
		public:
			/**/					FieldColumn (Glay::Int32u);

		protected:
			virtual const Value&	read (const Row&);

		private:
			Glay::Int32u	index;
	};
}

#endif

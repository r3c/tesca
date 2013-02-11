
#ifndef __TESCA_COLUMN_VALUE_HPP
#define __TESCA_COLUMN_VALUE_HPP

#include "../column.hpp"

namespace	Tesca
{
	class	ValueColumn : public Column
	{
		public:
			/**/	ValueColumn (const std::string&, const Reader*);

			virtual Slot*	create () const;
			virtual bool	key () const;
	};
}

#endif

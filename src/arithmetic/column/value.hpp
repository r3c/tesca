
#ifndef __TESCA_COLUMN_VALUE_HPP
#define __TESCA_COLUMN_VALUE_HPP

#include "../column.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	ValueColumn : public Column
		{
			public:
				ValueColumn (const std::string&, const Accessor*);

				virtual Slot*	create () const;
				virtual bool	group () const;
		};
	}
}

#endif

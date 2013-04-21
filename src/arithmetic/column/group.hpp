
#ifndef __TESCA_COLUMN_GROUP_HPP
#define __TESCA_COLUMN_GROUP_HPP

#include "../column.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		template<typename T>
		class GroupColumn : public Column
		{
			public:
				GroupColumn (const std::string&, const Accessor*);

				virtual Slot*	create () const;
				virtual bool	group () const;
		};
	}
}

#include "group.hxx"

#endif

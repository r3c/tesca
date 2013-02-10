
#ifndef __TESCA_COLUMN_GROUP_HPP
#define __TESCA_COLUMN_GROUP_HPP

#include "../column.hpp"

namespace	Tesca
{
	template<typename T>
	class GroupColumn : public Column
	{
		public:
			/**/	GroupColumn (const std::string&, const Reader*);

			virtual Slot*	create () const;
			virtual bool	key () const;
	};
}

#include "group.hxx"

#endif

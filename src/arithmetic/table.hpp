
#ifndef __TESCA_TABLE_HPP
#define __TESCA_TABLE_HPP

#include <map>
#include <vector>
#include "../glay/glay.hpp"
#include "bucket.hpp"
#include "column.hpp"
#include "row.hpp"
#include "slot.hpp"
#include "value.hpp"

namespace	Tesca
{
	class	Table
	{
		public:
			typedef std::vector<Column*>		Columns;
			typedef std::map<Bucket, Slot**>	Groups;

			typedef Groups::const_iterator		iterator;

			/**/			Table (const Table&);
			/**/			Table (Columns);
			/**/			~Table ();

			Table&			operator = (const Table&);

			Glay::Int32u	getWidth () const;

			iterator		begin () const;
			iterator		end () const;

			void			append (const Row&);
			void			reset ();

		private:
			typedef std::vector<const Value*>	Keys;
			typedef std::vector<Slot*>			Slots;

			Columns	columns;
			Groups	groups;
			Keys	keys;
			Slots	slots;
	};
}

#endif

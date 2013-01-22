
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
			typedef std::map<Bucket, Slot**>::const_iterator	iterator;

			/**/		Table (const Table&);
			/**/		Table (Column**, Glay::Int32u);
			/**/		~Table ();

			Table&		operator = (const Table&);

			iterator	begin () const;
			iterator	end () const;

			void		append (const Row&);
			void		reset ();

		private:
			Column**					columns;
			std::map<Bucket, Slot**>	groups;
			std::vector<const Value*>	keys;
			Glay::Int32u				size;
			std::vector<Slot*>			slots;
	};
}

#endif

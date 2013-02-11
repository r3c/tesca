
#ifndef __TESCA_TABLE_HPP
#define __TESCA_TABLE_HPP

#include <map>
#include <vector>
#include "../glay/glay.hpp"
#include "bucket.hpp"
#include "column.hpp"
#include "row.hpp"
#include "slot.hpp"
#include "variant.hpp"

namespace	Tesca
{
	class	Table
	{
		public:
			typedef std::vector<const Column*>	Columns;
			typedef std::map<Bucket, Slot**>	Groups;

			typedef Groups::const_iterator		iterator;

			/**/			Table (const Table&);
			/**/			Table (Columns);
			/**/			~Table ();

			Table&			operator = (const Table&);

			const Columns&	getColumns () const;
			Glay::Int32u	getWidth () const;

			iterator		begin () const;
			iterator		end () const;

			void			clear ();
			void			push (const Row&);

		private:
			typedef std::vector<Slot*>	Slots;

			Columns			columns;
			Glay::Int32u	keys;
			Groups			groups;
			Slots			slots;
	};
}

#endif


#ifndef __TESCA_ARITHMETIC_TABLE_HPP
#define __TESCA_ARITHMETIC_TABLE_HPP

#include <algorithm>
#include <map>
#include <vector>
#include "../glay/glay.hpp"
#include "../stream/row.hpp"
#include "../stream/variant.hpp"
#include "bucket.hpp"
#include "column.hpp"
#include "slot.hpp"

namespace	Tesca
{
	class	Table
	{
		public:
			typedef std::vector<const Column*>	Columns;
			typedef std::map<Bucket, Slot**>	Groups;
			typedef Groups::const_iterator		iterator;

			Table (const Table&);
			Table ();
			~Table ();

			Table&	operator = (const Table&);

			const Columns&	getColumns () const;
			Glay::Int32u	getWidth () const;

			iterator	begin () const;
			iterator	end () const;

			void	clear ();
			void	push (const Row&);
			void	reset (const Accessor*, const Columns&);

		private:
			typedef std::vector<Glay::Int32u>	Indices;
			typedef std::vector<Slot*>			Slots;

			Columns			columns;
			Indices			indices;
			Groups			groups;
			const Accessor*	select;
			Slots			slots;
	};
}

#endif

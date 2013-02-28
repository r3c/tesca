
#include "table.hpp"

#include "accessor/void.hpp"

using namespace Glay;
using namespace Tesca::Stream;

namespace	Tesca
{
	Table::Table () :
		select (&VoidAccessor::instance)
	{
	}

	Table::~Table ()
	{
		this->clear ();
	}

	const Table::Columns&	Table::getColumns () const
	{
		return this->columns;
	}

	Int32u	Table::getWidth () const
	{
		return this->columns.size ();
	}

	Table::iterator	Table::begin () const
	{
		return this->groups.begin ();
	}

	Table::iterator	Table::end () const
	{
		return this->groups.end ();
	}

	void	Table::clear ()
	{
		this->select = &VoidAccessor::instance;

		for (auto i = this->groups.begin (); i != this->groups.end (); ++i)
			delete [] i->second;

		for (auto i = this->slots.begin (); i != this->slots.end (); ++i)
			delete *i;

		this->groups.clear ();
		this->slots.clear ();
	}

	void	Table::push (const Row& row)
	{
		Bucket	bucket (this->indices.size ());
		bool	filter;
		Slot*	slot;
		Slot**	slots;
		Variant	values[this->columns.size ()];

		// Select row or exit if it should be discarded
		if (!this->select->read (row).toBoolean (&filter) || !filter)
			return;

		// Update columns and build bucket
		for (auto i = this->columns.size (); i-- > 0; )
			values[i] = this->columns[i]->read (row);

		for (auto i = this->indices.size (); i-- > 0; )
			bucket.set (i, values[this->indices[i]]);

		// Retrieve group from bucket or create it
		auto	found = this->groups.find (bucket);

		if (found == this->groups.end ())
		{
			slots = new Slot*[this->columns.size ()];

			for (auto i = this->columns.size (); i-- > 0; )
			{
				slot = this->columns[i]->create ();

				this->slots.push_back (slot);

				slots[i] = slot;
			}

			this->groups[bucket.keep ()] = slots;
		}
		else
			slots = found->second;

		// Append column values to group
		for (auto i = this->columns.size (); i-- > 0; )
			slots[i]->push (values[i]);
	}

	void	Table::reset (const Accessor* select, const Columns& columns)
	{
		Int32u	index;

		this->clear ();

		this->columns = columns;
		this->select = select;

		this->indices.clear ();

		index = 0;

		for (auto i = columns.begin (); i != columns.end (); ++i)
		{
			if ((*i)->group ())
				this->indices.push_back (index);

			++index;
		}
	}
}

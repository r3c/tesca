
#include "table.hpp"

using namespace Glay;

namespace	Tesca
{
	Table::Table (const Columns* columns) :
		columns (columns),
		keys (0),
		values (new Variant[columns->size ()])
	{
		for (auto i = columns->begin (); i != columns->end (); ++i)
		{
			if ((*i)->key ())
				++this->keys;
		}
	}

	Table::~Table ()
	{
		this->clear ();

		delete [] this->values;
	}

	const Table::Columns&	Table::getColumns () const
	{
		return *this->columns;
	}

	Int32u	Table::getWidth () const
	{
		return this->columns->size ();
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
		for (auto i = this->groups.begin (); i != this->groups.end (); ++i)
			delete [] i->second;

		for (auto i = this->slots.begin (); i != this->slots.end (); ++i)
			delete *i;

		this->groups.clear ();
		this->slots.clear ();
	}

	void	Table::push (const Row& row)
	{
		Bucket	bucket (this->keys);
		Int32u	index;
		Int32u	key;
		Slot*	slot;
		Slot**	slots;

		// Update columns and build bucket
		index = 0;
		key = 0;

		for (auto i = this->columns->begin (); i != this->columns->end (); ++i)
		{
			this->values[index] = (*i)->read (row);

			if ((*i)->key ())
				bucket.set (key++, this->values[index]);

			++index;
		}

		// Retrieve group from bucket or create it
		auto	found = this->groups.find (bucket);

		if (found == this->groups.end ())
		{
			index = 0;
			slots = new Slot*[this->columns->size ()];

			for (auto i = this->columns->begin (); i != this->columns->end (); ++i)
			{
				slot = (*i)->create ();

				this->slots.push_back (slot);

				slots[index++] = slot;
			}

			this->groups[bucket] = slots;
		}
		else
			slots = found->second;

		// Append column values to group
		for (Int32u i = this->columns->size (); i-- > 0; )
			slots[i]->push (this->values[i]);
	}
}

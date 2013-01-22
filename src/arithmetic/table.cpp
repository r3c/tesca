
#include "table.hpp"

using namespace Glay;

namespace	Tesca
{
	Table::Table (Column** columns, Int32u size) :
		columns (columns),
		size (size)
	{
	}

	Table::~Table ()
	{
		this->reset ();
	}

	Table::iterator	Table::begin () const
	{
		return this->groups.begin ();
	}

	Table::iterator	Table::end () const
	{
		return this->groups.end ();
	}

	void	Table::append (const Row& row)
	{
		Bucket	bucket (this->size);
		Slot**	slots;

		// Update columns and build bucket
		for (Int32u i = this->size; i-- > 0; )
		{
			Column&	column = *this->columns[i];

			column.update (row);

			bucket.set (i, &column.key ());
		}

		// Retrieve group from bucket or create it
		auto	iterator = this->groups.find (bucket);

		if (iterator == this->groups.end ())
		{
			slots = new Slot*[this->size];

			for (Int32u i = this->size; i-- > 0; )
			{
				const Column&	column = *this->columns[i];
				const Value*	key = column.key ().clone ();
				Slot*			slot = column.create ();

				this->keys.push_back (key);
				this->slots.push_back (slot);

				bucket.set (i, key);

				slots[i] = slot;
			}

			this->groups[bucket] = slots;
		}
		else
			slots = iterator->second;

		// Append column values to group
		for (Int32u i = this->size; i-- > 0; )
			slots[i]->append (this->columns[i]->value ());
	}

	void	Table::reset ()
	{
		for (auto i = this->keys.begin (); i != this->keys.end (); ++i)
			delete *i;

		for (auto i = this->groups.begin (); i != this->groups.end (); ++i)
			delete [] i->second;

		for (auto i = this->slots.begin (); i != this->slots.end (); ++i)
			delete *i;
	}
}

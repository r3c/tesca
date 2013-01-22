
#include "value.hpp"

#include "../slot/last.hpp"
#include "../value/void.hpp"

namespace	Tesca
{
	ValueColumn::ValueColumn () :
		current (&VoidValue::instance)
	{
	}

	Slot*	ValueColumn::create () const
	{
		return new LastSlot ();
	}

	const Value&	ValueColumn::key () const
	{
		return *this->current;
	}

	void	ValueColumn::update (const Row& row)
	{
		this->current = &this->read (row);
	}

	const Value&	ValueColumn::value () const
	{
		return *this->current;
	}
}

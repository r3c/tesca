
#include "last.hpp"

#include "../value/void.hpp"

namespace	Tesca
{
	LastSlot::LastSlot () :
		last (0)
	{
	}

	LastSlot::~LastSlot ()
	{
		if (this->last != 0)
			delete this->last;
	}

	void	LastSlot::append (const Value& value)
	{
		if (this->last == 0 || *this->last != value)
		{
			if (this->last != 0)
				delete this->last;

			this->last = value.clone ();
		}
	}

	const Value&	LastSlot::value () const
	{
		if (this->last != 0)
			return *this->last;

		return VoidValue::instance;
	}
}

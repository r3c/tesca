
#include "last.hpp"

using namespace Glay;

namespace	Tesca
{
	Variant	LastSlot::current () const
	{
		return this->last;
	}

	bool	LastSlot::push (const Variant& value)
	{
		this->last = value;

		return true;
	}

	void	LastSlot::reset ()
	{
		this->last = Variant::empty;
	}
}

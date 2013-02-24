
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
		this->last.keep ();

		return true;
	}

	void	LastSlot::reset ()
	{
		this->last = Variant::empty;
	}
}

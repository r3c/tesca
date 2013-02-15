
#include "value.hpp"

#include "../slot/last.hpp"

using namespace std;

namespace	Tesca
{
	ValueColumn::ValueColumn (const string& identifier, const Accessor* accessor) :
		Column (identifier, accessor)
	{
	}

	Slot*	ValueColumn::create () const
	{
		return new LastSlot ();
	}

	bool	ValueColumn::key () const
	{
		return true;
	}
}

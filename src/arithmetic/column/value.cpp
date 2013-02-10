
#include "value.hpp"

#include "../slot/last.hpp"

using namespace std;

namespace	Tesca
{
	ValueColumn::ValueColumn (const string& identifier, const Reader* reader) :
		Column (identifier, reader)
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


#include "value.hpp"

#include "../slot/first.hpp"

using namespace std;

namespace	Tesca
{
	namespace	Arithmetic
	{
		ValueColumn::ValueColumn (const string& identifier, const Accessor* accessor) :
			Column (identifier, accessor)
		{
		}

		Slot*	ValueColumn::create () const
		{
			return new FirstSlot ();
		}

		bool	ValueColumn::group () const
		{
			return true;
		}
	}
}


#include "group.hpp"

using namespace std;

namespace	Tesca
{
	template<typename T>
	GroupColumn<T>::GroupColumn (const string& identifier, const Accessor* accessor) :
		Column (identifier, accessor)
	{
	}

	
	template<typename T>
	Slot*	GroupColumn<T>::create () const
	{
		return new T ();
	}

	template<typename T>
	bool	GroupColumn<T>::group () const
	{
		return false;
	}
}

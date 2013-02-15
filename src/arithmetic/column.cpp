
#include "column.hpp"

using namespace std;

namespace	Tesca
{
	Column::Column (const string& identifier, const Accessor* accessor) :
		accessor (accessor),
		identifier (identifier)
	{
	}

	const string&	Column::getIdentifier () const
	{
		return this->identifier;
	}

	Variant	Column::read (const Row& row) const
	{
		return this->accessor->read (row);
	}
}

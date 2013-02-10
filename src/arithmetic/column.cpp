
#include "column.hpp"

using namespace std;

namespace	Tesca
{
	Column::Column (const string& identifier, const Reader* reader) :
		identifier (identifier),
		reader (reader)
	{
	}

	const string&	Column::getIdentifier () const
	{
		return this->identifier;
	}

	Variant	Column::read (const Row& row) const
	{
		return this->reader->read (row);
	}
}

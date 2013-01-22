
#include "field.hpp"

using namespace Glay;

namespace	Tesca
{
	FieldColumn::FieldColumn (Int32u index) :
		index (index)
	{
	}

	const Value&	FieldColumn::read (const Row& row)
	{
		return row[this->index];
	}
}

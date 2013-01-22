
#include "row.hpp"

#include "value/void.hpp"

using namespace Glay;

namespace	Tesca
{
// FIXME
Row::Row (const Value** values) :
	values (values)
{
}
// FIXME

	Row::Row ()
	{
	}

	const Value&	Row::operator [] (Int32u index) const
	{
		return *this->values[index];
	}
}

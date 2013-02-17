
#include "field.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	FieldAccessor::FieldAccessor (Int32u key) :
		key (key)
	{
	}

	Variant	FieldAccessor::read (const Row& row) const
	{
		return row[this->key];
	}
}

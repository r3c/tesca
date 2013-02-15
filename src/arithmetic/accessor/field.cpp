
#include "field.hpp"

using namespace std;

namespace	Tesca
{
	FieldAccessor::FieldAccessor (const string& identifier) :
		identifier (identifier)
	{
	}

	Variant	FieldAccessor::read (const Row& row) const
	{
		return row[this->identifier];
	}
}


#include "field.hpp"

using namespace std;

namespace	Tesca
{
	FieldReader::FieldReader (const string& identifier) :
		identifier (identifier)
	{
	}

	Variant	FieldReader::read (const Row& row) const
	{
		return row[this->identifier];
	}
}

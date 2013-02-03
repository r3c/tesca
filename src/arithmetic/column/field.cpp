
#include "field.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	FieldColumn::FieldColumn (const string& key) :
		key (key)
	{
	}

	const Value&	FieldColumn::read (const Row& row)
	{
		return row[this->key];
	}
}

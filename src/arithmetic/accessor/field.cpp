
#include "field.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
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
}

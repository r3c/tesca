
#include "field.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		FieldExtractor::FieldExtractor (Int32u field) :
			field (field)
		{
		}

		Int32u	FieldExtractor::getFlags () const
		{
			return SCALAR;
		}

		Variant	FieldExtractor::compute (const Aggregator* const*) const
		{
			return Variant::empty;
		}

		Variant	FieldExtractor::extract (const Row& row) const
		{
			return row[this->field];
		}
	}
}

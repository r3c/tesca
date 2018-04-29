
#include "field.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		FieldExtractor::FieldExtractor (Int32u field, const string& name) :
			field (field),
			name (name)
		{
		}

		string FieldExtractor::createName (Int32u) const
		{
			return this->name;
		}

		Int32u FieldExtractor::getFlags () const
		{
			return SCALAR;
		}

		Variant FieldExtractor::compute (const Aggregator* const*) const
		{
			return Variant::empty;
		}

		Variant FieldExtractor::extract (const Row& row) const
		{
			return row[this->field];
		}
	}
}

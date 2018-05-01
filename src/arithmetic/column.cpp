
#include "column.hpp"

using namespace std;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		Column::Column (Column const& other) :
			extractor (other.extractor),
			key (other.key)
		{
		}

		Column::Column (const string& key, Extractor const* extractor) :
			extractor (extractor),
			key (key)
		{
		}

		Column::Column () :
			extractor (0),
			key ()
		{
		}

		Column& Column::operator = (Column const& other)
		{
			this->extractor = other.extractor;
			this->key = other.key;

			return *this;
		}

		Extractor const* Column::getExtractor () const
		{
			return this->extractor;
		}

		const string& Column::getKey () const
		{
			return this->key;
		}
	}
}

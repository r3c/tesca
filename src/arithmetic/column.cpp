
#include "column.hpp"

using namespace std;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		Column::Column (const Column& other) :
			extractor (other.extractor),
			key (other.key)
		{
		}

		Column::Column (const string& key, const Extractor* extractor) :
			extractor (extractor),
			key (key)
		{
		}

		Column::Column () :
			extractor (0),
			key ()
		{
		}

		Column&	Column::operator = (const Column& other)
		{
			this->extractor = other.extractor;
			this->key = other.key;

			return *this;
		}

		const Extractor*	Column::getExtractor () const
		{
			return this->extractor;
		}

		const string&	Column::getKey () const
		{
			return this->key;
		}
	}
}

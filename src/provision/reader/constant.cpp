
#include "constant.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Provision
	{
		ConstantReader::ConstantReader (Lookup const& lookup, Int32u count) :
			count (count),
			lookup (lookup),
			row (lookup.count ())
		{
		}

		bool ConstantReader::assign (const string& identifier, Variant const& value)
		{
			Int32u field;

			if (!this->lookup.find (identifier, &field))
				return false;

			this->row.set (field, value);

			return true;
		}

		Row const& ConstantReader::current () const
		{
			return this->row;
		}

		bool ConstantReader::next ()
		{
			if (this->count <= 0)
				return false;

			--this->count;

			return true;
		}
	}
}

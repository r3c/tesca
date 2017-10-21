
#include "map.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Provision
	{
		MapReader::MapReader (const Fields* fields) :
			fields (fields),
			row (fields->size ())
		{
		}

		MapReader::~MapReader ()
		{
			for (auto i = this->lines.begin (); i != this->lines.end (); ++i)
				delete [] *i;
		}

		bool MapReader::assign (const string& identifier, const Variant& value)
		{
			Variant copy;
			Variant* line;

			auto field = this->fields->find (identifier);

			if (field == this->fields->end () || this->lines.empty ())
				return false;

			copy = value;
			copy.keep ();

			line = this->lines.back ();
			line[field->second] = copy;

			return true;
		}

		const Row& MapReader::current () const
		{
			return this->row;
		}

		bool MapReader::next ()
		{
			Variant* values;

			this->row.clear ();

			if (this->lines.empty ())
				return false;

			values = this->lines.front ();

			for (auto i = this->fields->size (); i-- > 0; )
				this->row.set (i, values[i]);

			delete [] values;

			this->lines.pop_front ();

			return true;
		}

		void MapReader::push ()
		{
			this->lines.push_back (new Variant[this->fields->size ()]);
		}
	}
}

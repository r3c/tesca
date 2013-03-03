
#include "lookup.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	namespace	Provision
	{
		Lookup::Lookup ()
		{
		}

		Lookup::const_iterator	Lookup::begin () const
		{
			return this->indices.begin ();
		}

		Lookup::const_iterator	Lookup::end () const
		{
			return this->indices.end ();
		}

		Int32u	Lookup::count () const
		{
			return this->indices.size ();
		}

		bool	Lookup::find (const string& key, Int32u* index) const
		{
			auto	i = this->indices.find (key);

			if (i == this->indices.end ())
				return false;

			*index = i->second;

			return true;
		}

		Int32u	Lookup::set (const string& key)
		{
			Int32u	index;

			if (!this->find (key, &index))
			{
				index = this->indices.size ();

				this->indices[key] = index;
			}

			return index;
		}
	}
}

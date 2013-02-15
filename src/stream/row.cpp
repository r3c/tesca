
#include "row.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	Row::Row ()
	{
	}

	const Variant&	Row::operator [] (string key) const
	{
		auto	i = this->fields.find (key);

		if (i != this->fields.end ())
			return i->second;

		return Variant::empty;
	}

	void	Row::clear ()
	{
		this->fields.clear ();
	}

	void	Row::push (const string& identifier, const Variant& value)
	{
		this->fields[identifier] = value;
	}
}

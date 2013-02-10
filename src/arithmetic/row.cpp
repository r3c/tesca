
#include "row.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
// FIXME
Row::Row (const map<string, const Variant*>& values) :
	values (values)
{
}
// FIXME

	const Variant&	Row::operator [] (string key) const
	{
		map<string, const Variant*>::const_iterator	i = this->values.find (key);

		if (i != this->values.end ())
			return *i->second;

		return Variant::empty;
	}
}

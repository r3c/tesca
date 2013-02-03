
#include "row.hpp"

#include "value/void.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
// FIXME
Row::Row (const map<string, const Value*>& values) :
	values (values)
{
}
// FIXME

	const Value&	Row::operator [] (string key) const
	{
		map<string, const Value*>::const_iterator	i = this->values.find (key);

		if (i != this->values.end ())
			return *i->second;

		return VoidValue::instance;
	}
}

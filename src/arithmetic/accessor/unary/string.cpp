
#include "string.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	StringUnaryAccessor::StringUnaryAccessor (const Accessor* source, Callback callback) :
		UnaryAccessor (source),
		callback (callback)
	{
	}

	Variant	StringUnaryAccessor::evaluate (const Variant& argument) const
	{
		string	str;

		if (argument.toString (&str))
			return this->callback (str);

		return Variant::empty;
	}
}

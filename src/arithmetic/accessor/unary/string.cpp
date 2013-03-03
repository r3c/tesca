
#include "string.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Provision;

namespace	Tesca
{
	StringUnaryAccessor::StringUnaryAccessor (const Accessor* source, Callback callback) :
		UnaryAccessor (source),
		callback (callback)
	{
	}

	Variant	StringUnaryAccessor::evaluate (const Variant& argument) const
	{
		string	value;

		if (argument.toString (&value))
			return this->callback (value);

		return Variant::empty;
	}
}

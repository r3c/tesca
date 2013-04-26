
#include "boolean.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		BooleanUnaryAccessor::BooleanUnaryAccessor (const Accessor* source, Callback callback) :
			UnaryAccessor (source),
			callback (callback)
		{
		}

		Variant	BooleanUnaryAccessor::evaluate (const Variant& argument) const
		{
			bool	value;

			if (argument.toBoolean (&value))
				return this->callback (value);

			return Variant::empty;
		}
	}
}


#include "number.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		NumberUnaryAccessor::NumberUnaryAccessor (const Accessor* source, Callback callback) :
			UnaryAccessor (source),
			callback (callback)
		{
		}

		Variant	NumberUnaryAccessor::evaluate (const Variant& argument) const
		{
			Float64	value;

			if (argument.toNumber (&value))
				return this->callback (value);

			return Variant::empty;
		}
	}
}

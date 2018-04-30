
#include "wrapper.hpp"

#include <string> 

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Expression
	{
		function<Variant (const Variant&)> booleanUnary (function<Variant (bool)> booleanCallback)
		{
			return [=] (const Variant& argument) -> Variant
			{
				bool value;

				if (argument.toBoolean (&value))
					return booleanCallback (value);

				return Variant::empty;
			};
		}

		function<Variant (const Variant&)> numberUnary (function<Variant (Float64)> numberCallback)
		{
			return [=] (const Variant& argument) -> Variant
			{
				Float64 value;

				if (argument.toNumber (&value))
					return numberCallback (value);

				return Variant::empty;
			};
		}

		function<Variant (const Variant&)> stringUnary (function<Variant (const string&)> stringCallback)
		{
			return [=] (const Variant& argument) -> Variant
			{
				string value;

				if (argument.toString (&value))
					return stringCallback (value);

				return Variant::empty;
			};
		}
	}
}
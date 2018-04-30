
#include "wrapper.hpp"

#include <string> 

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Expression
	{
		function<Variant (const Variant&)> wrapBoolean (function<Variant (bool)> booleanCallback)
		{
			return [=] (const Variant& argument) -> Variant
			{
				bool value;

				return argument.toBoolean (&value)
					? booleanCallback (value)
					: Variant::empty;
			};
		}

		function<Variant (const Variant&, const Variant&)> wrapNumber (function<Variant (Float64, Float64)> numberCallback)
		{
			return [=] (const Variant& lhs, const Variant& rhs) -> Variant
			{
				Float64 lhsNumber;
				Float64 rhsNumber;

				return lhs.toNumber (&lhsNumber) && rhs.toNumber (&rhsNumber) ? numberCallback (lhsNumber, rhsNumber) : Variant::empty;
			};
		}

		function<Variant (const Variant&)> wrapNumber (function<Variant (Float64)> numberCallback)
		{
			return [=] (const Variant& argument) -> Variant
			{
				Float64 value;

				return argument.toNumber (&value)
					? numberCallback (value)
					: Variant::empty;
			};
		}

		function<Variant (const Variant&)> wrapString (function<Variant (const string&)> stringCallback)
		{
			return [=] (const Variant& argument) -> Variant
			{
				string value;

				return argument.toString (&value)
					? stringCallback (value)
					: Variant::empty;
			};
		}
	}
}
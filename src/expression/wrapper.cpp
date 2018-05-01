
#include "wrapper.hpp"

#include <string> 

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Expression
	{
		function<Variant (Variant const&)> wrapBoolean (function<Variant (bool)> booleanCallback)
		{
			return [=] (Variant const& argument) -> Variant
			{
				bool value;

				return argument.toBoolean (&value)
					? booleanCallback (value)
					: Variant::empty;
			};
		}

		function<Variant (Variant const&, Variant const&)> wrapNumber (function<Variant (Float64, Float64)> numberCallback)
		{
			return [=] (Variant const& lhs, Variant const& rhs) -> Variant
			{
				Float64 lhsNumber;
				Float64 rhsNumber;

				return lhs.toNumber (&lhsNumber) && rhs.toNumber (&rhsNumber) ? numberCallback (lhsNumber, rhsNumber) : Variant::empty;
			};
		}

		function<Variant (Variant const&)> wrapNumber (function<Variant (Float64)> numberCallback)
		{
			return [=] (Variant const& argument) -> Variant
			{
				Float64 value;

				return argument.toNumber (&value)
					? numberCallback (value)
					: Variant::empty;
			};
		}

		function<Variant (Variant const&)> wrapString (function<Variant (const string&)> stringCallback)
		{
			return [=] (Variant const& argument) -> Variant
			{
				string value;

				return argument.toString (&value)
					? stringCallback (value)
					: Variant::empty;
			};
		}
	}
}
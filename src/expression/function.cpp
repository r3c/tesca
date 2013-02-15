
#include "function.hpp"

#include <algorithm>
#include <string> 
#include "../arithmetic/accessor/binary.hpp"
#include "../arithmetic/accessor/constant.hpp"
#include "../arithmetic/accessor/field.hpp"
#include "../arithmetic/accessor/unary.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	const Function	Function::functions[] =
	{
		{"add",		2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new BinaryAccessor (arguments[0], arguments[1], [] (const Variant& lhs, const Variant& rhs)
			{
				Float64	a;
				Float64	b;

				if (lhs.toNumber (&a) && rhs.toNumber (&b))
					return Variant (a + b);

				return Variant::empty;
			});
		}},
		{"lcase",	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new UnaryAccessor (arguments[0], [] (const Variant& source)
			{
				string	buffer;

				if (!source.toString (&buffer))
					return Variant::empty;

				transform (buffer.begin (), buffer.end (), buffer.begin (), ::tolower);

				return Variant (buffer);
			});
		}},
		{"ucase",	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new UnaryAccessor (arguments[0], [] (const Variant& source)
			{
				string	buffer;

				if (!source.toString (&buffer))
					return Variant::empty;

				transform (buffer.begin (), buffer.end (), buffer.begin (), ::toupper);

				return Variant (buffer);
			});
		}},
		{0, 0, 0}
	};
}

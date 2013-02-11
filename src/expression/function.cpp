
#include "function.hpp"

#include <algorithm>
#include <string> 
#include "../arithmetic/reader/binary.hpp"
#include "../arithmetic/reader/constant.hpp"
#include "../arithmetic/reader/field.hpp"
#include "../arithmetic/reader/unary.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	const Function	Function::functions[] =
	{
		{"add",		2,	[] (const vector<const Reader*>& arguments) -> Reader*
		{
			return new BinaryReader (arguments[0], arguments[1], [] (const Variant& lhs, const Variant& rhs)
			{
				Float64	a;
				Float64	b;

				if (lhs.toNumber (&a) && rhs.toNumber (&b))
					return Variant (a + b);

				return Variant::empty;
			});
		}},
		{"lcase",	1,	[] (const vector<const Reader*>& arguments) -> Reader*
		{
			return new UnaryReader (arguments[0], [] (const Variant& source)
			{
				string	buffer;

				if (!source.toString (&buffer))
					return Variant::empty;

				transform (buffer.begin (), buffer.end (), buffer.begin (), ::tolower);

				return Variant (buffer);
			});
		}},
		{"ucase",	1,	[] (const vector<const Reader*>& arguments) -> Reader*
		{
			return new UnaryReader (arguments[0], [] (const Variant& source)
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

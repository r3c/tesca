
#include "function.hpp"

#include <algorithm>
#include <string> 
#include "../arithmetic/accessor/binary/callback.hpp"
#include "../arithmetic/accessor/binary/number.hpp"
#include "../arithmetic/accessor/constant.hpp"
#include "../arithmetic/accessor/field.hpp"
#include "../arithmetic/accessor/unary/callback.hpp"
#include "../arithmetic/accessor/unary/string.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	const Function	Function::functions[] =
	{
		{"add",		2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return Variant (a + b);
			});
		}},
		{"div",		2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return b != 0 ? Variant (a / b) : Variant::empty;
			});
		}},
		{"lcase",	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new StringUnaryAccessor (arguments[0], [] (string& argument)
			{
				transform (argument.begin (), argument.end (), argument.begin (), ::tolower);

				return Variant (argument);
			});
		}},
		{"mod",		2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return b != 0 ? Variant (fmod (a, b)) : Variant::empty;
			});
		}},
		{"mul",		2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return Variant (a * b);
			});
		}},
		{"sub",		2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return Variant (a - b);
			});
		}},
		{"ucase",	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new StringUnaryAccessor (arguments[0], [] (string& argument)
			{
				transform (argument.begin (), argument.end (), argument.begin (), ::toupper);

				return Variant (argument);
			});
		}},
		{0, 0, 0}
	};
}

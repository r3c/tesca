
#include "function.hpp"

#include <algorithm>
#include <string> 
#include "../arithmetic/accessor/binary/callback.hpp"
#include "../arithmetic/accessor/binary/number.hpp"
#include "../arithmetic/accessor/constant.hpp"
#include "../arithmetic/accessor/field.hpp"
#include "../arithmetic/accessor/if.hpp"
#include "../arithmetic/accessor/logical/and.hpp"
#include "../arithmetic/accessor/logical/or.hpp"
#include "../arithmetic/accessor/unary/callback.hpp"
#include "../arithmetic/accessor/unary/string.hpp"
#include "../arithmetic/accessor/vector/callback.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	const Function	Function::functions[] =
	{
		{"add",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return Variant (a + b);
			});
		}},
		{"and",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new AndLogicalAccessor (arguments[0], arguments[1]);
		}},
		{"cmp",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackBinaryAccessor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
			{
				return Variant (a.compare (b));
			});
		}},
		{"div",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return b != 0 ? Variant (a / b) : Variant::empty;
			});
		}},
		{"eq",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackBinaryAccessor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
			{
				return Variant (a == b);
			});
		}},
		{"ge",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackBinaryAccessor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
			{
				return Variant (a >= b);
			});
		}},
		{"gt",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackBinaryAccessor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
			{
				return Variant (a > b);
			});
		}},
		{"if",		2,	3,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			if (arguments.size () == 3)
				return new IfAccessor (arguments[0], arguments[1], arguments[2]);
			else
				return new IfAccessor (arguments[0], arguments[1]);
		}},
		{"lcase",	1,	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new StringUnaryAccessor (arguments[0], [] (string& argument)
			{
				transform (argument.begin (), argument.end (), argument.begin (), ::tolower);

				return Variant (argument).keep ();
			});
		}},
		{"le",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackBinaryAccessor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
			{
				return Variant (a <= b);
			});
		}},
		{"lt",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackBinaryAccessor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
			{
				return Variant (a < b);
			});
		}},
		{"max",		1,	0,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackVectorAccessor (arguments, [] (const Variant* values, Int32u length)
			{
				bool	defined;
				Float64	number;
				Float64	result;

				defined = false;
				result = 0;

				for (; length-- > 0; ++values)
				{
					if (values->toNumber (&number) && (!defined || number > result))
					{
						defined = true;
						result = number;
					}
				}

				return defined ? Variant (result) : Variant::empty;
			});
		}},
		{"min",		1,	0,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackVectorAccessor (arguments, [] (const Variant* values, Int32u length)
			{
				bool	defined;
				Float64	number;
				Float64	result;

				defined = false;
				result = 0;

				for (; length-- > 0; ++values)
				{
					if (values->toNumber (&number) && (!defined || number < result))
					{
						defined = true;
						result = number;
					}
				}

				return defined ? Variant (result) : Variant::empty;
			});
		}},
		{"mod",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return b != 0 ? Variant (fmod (a, b)) : Variant::empty;
			});
		}},
		{"mul",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return Variant (a * b);
			});
		}},
		{"ne",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackBinaryAccessor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
			{
				return Variant (a != b);
			});
		}},
		{"not",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new CallbackUnaryAccessor (arguments[0], [] (const Variant& argument)
			{
				bool	value;

				return Variant (!argument.toBoolean (&value) || !value);
			});
		}},
		{"or",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new OrLogicalAccessor (arguments[0], arguments[1]);
		}},
		{"sub",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new NumberBinaryAccessor (arguments[0], arguments[1], [] (Float64 a, Float64 b)
			{
				return Variant (a - b);
			});
		}},
		{"ucase",	1,	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
		{
			return new StringUnaryAccessor (arguments[0], [] (string& argument)
			{
				transform (argument.begin (), argument.end (), argument.begin (), ::toupper);

				return Variant (argument).keep ();
			});
		}},
		{0, 0, 0, 0}
	};
}

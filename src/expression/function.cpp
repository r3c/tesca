
#include "function.hpp"

#include <algorithm>
#include <string> 
#include "../arithmetic/accessor/binary/callback.hpp"
#include "../arithmetic/accessor/binary/number.hpp"
#include "../arithmetic/accessor/if.hpp"
#include "../arithmetic/accessor/unary/callback.hpp"
#include "../arithmetic/accessor/unary/string.hpp"
#include "../arithmetic/accessor/vector/callback.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Arithmetic;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Expression
	{
		const Function	Function::functions[] =
		{
			{"cmp",		2,	2,	[] (const vector<const Accessor*>& arguments) -> Accessor*
			{
				return new CallbackBinaryAccessor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
				{
					return Variant (a.compare (b));
				});
			}},
			{"if",		2,	3,	[] (const vector<const Accessor*>& arguments) -> Accessor*
			{
				if (arguments.size () == 3)
					return new IfAccessor (arguments[0], arguments[1], arguments[2]);
				else
					return new IfAccessor (arguments[0], arguments[1]);
			}},
			{"in",		1,	0,	[] (const vector<const Accessor*>& arguments) -> Accessor*
			{
				return new CallbackVectorAccessor (arguments, [] (const Variant* values, Int32u length)
				{
					const Variant*	search;

					search = values++;

					for (; length-- > 1; ++values)
					{
						if (search->compare (*values) == 0)
							return Variant (true);
					}

					return Variant (false);
				});
			}},
			{"lcase",	1,	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
			{
				return new StringUnaryAccessor (arguments[0], [] (const string& argument)
				{
					char*	buffer;
					Variant	lower;

					buffer = new char[argument.length ()];

					for (auto i = argument.length (); i-- > 0; )
						buffer[i] = tolower (argument[i]);

					lower = Variant (buffer, argument.length ()).keep ();

					delete [] buffer;

					return lower;
				});
			}},
			{"len",		1,	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
			{
				return new StringUnaryAccessor (arguments[0], [] (const string& argument)
				{
					return Variant (argument.length ());
				});
			}},
			{"max",		0,	0,	[] (const vector<const Accessor*>& arguments) -> Accessor*
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
			{"min",		0,	0,	[] (const vector<const Accessor*>& arguments) -> Accessor*
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
			{"slice",	2,	3,	[] (const vector<const Accessor*>& arguments) -> Accessor*
			{
				return new CallbackVectorAccessor (arguments, [] (const Variant* values, Int32u length)
				{
					Float64	count;
					string	source;
					Float64	number;
					Int32u	offset;

					if (!values[0].toString (&source) || !values[1].toNumber (&number))
						return Variant::empty;

					offset = std::min ((Int32u)number, source.length ());

					if (length > 2)
					{
						if (!values[2].toNumber (&number))
							return Variant::empty;

						count = std::min ((Int32u)number, source.length () - offset);
					}
					else
						count = source.length () - offset;

					return Variant (source.substr (offset, count)).keep ();
				});
			}},
			{"ucase",	1,	1,	[] (const vector<const Accessor*>& arguments) -> Accessor*
			{
				return new StringUnaryAccessor (arguments[0], [] (const string& argument)
				{
					char*	buffer;
					Variant	upper;

					buffer = new char[argument.length ()];

					for (auto i = argument.length (); i-- > 0; )
						buffer[i] = toupper (argument[i]);

					upper = Variant (buffer, argument.length ()).keep ();

					delete [] buffer;

					return upper;
				});
			}},
			{0, 0, 0, 0}
		};
	}
}

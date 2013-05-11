
#include "function.hpp"

#include <algorithm>
#include <string> 
#include "../arithmetic/aggregator/average.hpp"
#include "../arithmetic/aggregator/count.hpp"
#include "../arithmetic/aggregator/first.hpp"
#include "../arithmetic/aggregator/last.hpp"
#include "../arithmetic/aggregator/sum.hpp"
#include "../arithmetic/aggregator/variance.hpp"
#include "../arithmetic/extractor/binary/callback.hpp"
#include "../arithmetic/extractor/binary/number.hpp"
#include "../arithmetic/extractor/if.hpp"
#include "../arithmetic/extractor/slot/constant.hpp"
#include "../arithmetic/extractor/slot/reduce.hpp"
#include "../arithmetic/extractor/unary/callback.hpp"
#include "../arithmetic/extractor/unary/string.hpp"
#include "../arithmetic/extractor/vector/callback.hpp"

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
			{"avg",		1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceSlotExtractor<AverageAggregator> ((*slot)++, arguments[0]);
			}},
			{"cmp",		2,	2,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackBinaryExtractor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
				{
					return Variant (a.compare (b));
				});
			}},
			{"count",	0,	0,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ConstantSlotExtractor<CountAggregator> ((*slot)++, Variant::empty);
			}},
			{"first",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceSlotExtractor<FirstAggregator> ((*slot)++, arguments[0]);
			}},
			{"if",		2,	3,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				if (arguments.size () == 3)
					return new IfExtractor (arguments[0], arguments[1], arguments[2]);
				else
					return new IfExtractor (arguments[0], arguments[1]);
			}},
			{"in",		1,	0,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u length)
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
			{"last",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceSlotExtractor<LastAggregator> ((*slot)++, arguments[0]);
			}},
			{"lcase",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new StringUnaryExtractor (arguments[0], [] (const string& argument)
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
			{"len",		1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new StringUnaryExtractor (arguments[0], [] (const string& argument)
				{
					return Variant (argument.length ());
				});
			}},
			{"max",		0,	0,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u length)
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
			{"min",		0,	0,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u length)
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
			{"slice",	2,	3,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u length)
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
			{"sum",		1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceSlotExtractor<SumAggregator> ((*slot)++, arguments[0]);
			}},
			{"ucase",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new StringUnaryExtractor (arguments[0], [] (const string& argument)
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
			{"var",		1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceSlotExtractor<VarianceAggregator> ((*slot)++, arguments[0]);
			}},
			{0, 0, 0, 0}
		};
	}
}

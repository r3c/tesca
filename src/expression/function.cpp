
#include "function.hpp"

#include <algorithm>
#include <cmath>
#include <string> 
#include "../arithmetic/aggregator/average.hpp"
#include "../arithmetic/aggregator/count.hpp"
#include "../arithmetic/aggregator/first.hpp"
#include "../arithmetic/aggregator/last.hpp"
#include "../arithmetic/aggregator/max.hpp"
#include "../arithmetic/aggregator/min.hpp"
#include "../arithmetic/aggregator/sum.hpp"
#include "../arithmetic/aggregator/variance.hpp"
#include "../arithmetic/extractor/binary/number.hpp"
#include "../arithmetic/extractor/binary/variant.hpp"
#include "../arithmetic/extractor/composite/constant.hpp"
#include "../arithmetic/extractor/composite/reduce.hpp"
#include "../arithmetic/extractor/if.hpp"
#include "../arithmetic/extractor/unary/number.hpp"
#include "../arithmetic/extractor/unary/string.hpp"
#include "../arithmetic/extractor/vector/callback.hpp"
#include "../arithmetic/extractor/vector/lazy.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Arithmetic;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Expression
	{
		const Function Function::functions[] =
		{
			{"abs",		1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new NumberUnaryExtractor (arguments[0], [] (Float64 value)
				{
					return Variant (fabs (value));
				});
			}},
			{"at",		1,	0,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new LazyVectorExtractor (arguments, [] (LazyVectorExtractor::Resolver resolver, Int32u count)
				{
					Int32u index;
					Float64 value;

					if (resolver (0).toNumber (&value) && value >= 0)
					{
						index = (Int32u)value;

						if (index + 1 < count)
							return resolver (index + 1);
					}

					return Variant::empty;
				});
			}},
			{"avg",		1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<AverageAggregator> ((*slot)++, arguments[0]);
			}},
			{"case",	2,	0,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new LazyVectorExtractor (arguments, [] (LazyVectorExtractor::Resolver resolver, Int32u count)
				{
					Int32u index;
					const Variant& search = resolver (0);

					for (index = 1; index + 1 < count; index += 2)
					{
						if (search.compare (resolver (index)) == 0)
							return resolver (index + 1);
					}

					if (index < count)
						return resolver (index);

					return Variant::empty;
				});
			}},
			{"ceil",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new NumberUnaryExtractor (arguments[0], [] (Float64 value)
				{
					return Variant (ceil (value));
				});
			}},
			{"cmp",		2,	2,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new VariantBinaryExtractor (arguments[0], arguments[1], [] (const Variant& a, const Variant& b)
				{
					return Variant (a.compare (b));
				});
			}},
			{"count",	0,	0,	[] (const vector<const Extractor*>&, Int32u* slot) -> Extractor*
			{
				return new ConstantCompositeExtractor<CountAggregator> ((*slot)++, Variant::empty);
			}},
			{"default",	1,	2,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u count)
				{
					bool test;

					if (values[0].toBoolean (&test) && test)
						return values[0];

					return count > 1 ? values[1] : Variant::empty;
				});
			}},
			{"find",	2,	3,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u count)
				{
					size_t position;
					string source;
					string search;
					Int32u start;
					Float64 value;

					if (!values[0].toString (&source) || !values[1].toString (&search))
						return Variant::empty;

					if (count > 2)
					{
						if (!values[2].toNumber (&value) || value < 0)
							return Variant::empty;

						start = std::min ((Int32u)value, source.length ());
					}
					else
						start = 0;

					position = source.find (search, start);

					return position != string::npos ? Variant (position) : Variant::empty;
				});
			}},
			{"first",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<FirstAggregator> ((*slot)++, arguments[0]);
			}},
			{"floor",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new NumberUnaryExtractor (arguments[0], [] (Float64 value)
				{
					return Variant (floor (value));
				});
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
				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u count)
				{
					const Variant* search;

					search = values++;

					for (; count-- > 1; ++values)
					{
						if (search->compare (*values) == 0)
							return Variant (true);
					}

					return Variant (false);
				});
			}},
			{"last",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<LastAggregator> ((*slot)++, arguments[0]);
			}},
			{"lcase",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new StringUnaryExtractor (arguments[0], [] (const string& argument)
				{
					char* buffer;
					Variant lower;

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
			{"log",		1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new NumberUnaryExtractor (arguments[0], [] (Float64 value)
				{
					if (value <= 0)
						return Variant::empty;

					return Variant (log (value));
				});
			}},
			{"max",		1,	0,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				if (arguments.size () == 1)
					return new ReduceCompositeExtractor<MaxAggregator> ((*slot)++, arguments[0]);

				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u count)
				{
					Float64 current;
					bool empty;
					Float64 max;

					empty = false;
					max = 0;

					for (; count-- > 0; ++values)
					{
						if (values->toNumber (&current) && (empty || current > max))
						{
							empty = false;
							max = current;
						}
					}

					return empty ? Variant::empty : Variant (max);
				});
			}},
			{"min",		1,	0,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				if (arguments.size () == 1)
					return new ReduceCompositeExtractor<MinAggregator> ((*slot)++, arguments[0]);

				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u count)
				{
					Float64 current;
					bool empty;
					Float64 min;

					empty = false;
					min = 0;

					for (; count-- > 0; ++values)
					{
						if (values->toNumber (&current) && (empty || current < min))
						{
							empty = false;
							min = current;
						}
					}

					return empty ? Variant::empty : Variant (min);
				});
			}},
			{"pow",		2,	2,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new NumberBinaryExtractor (arguments[0], arguments[1], [] (Float64 base, Float64 exponent)
				{
					return Variant (pow (base, exponent));
				});
			}},
			{"round",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new NumberUnaryExtractor (arguments[0], [] (Float64 value)
				{
					return Variant (round (value));
				});
			}},
			{"slice",	2,	3,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, [] (const Variant* values, Int32u count)
				{
					Int32u length;
					string source;
					Int32u start;
					Float64 value;

					if (!values[0].toString (&source) || !values[1].toNumber (&value))
						return Variant::empty;

					if (value < 0)
						start = std::min (source.length () + (Int32u)value, source.length ());
					else
						start = std::min ((Int32u)value, source.length ());

					if (count > 2)
					{
						if (!values[2].toNumber (&value) || value < 0)
							return Variant::empty;

						length = std::min ((Int32u)value, source.length () - start);
					}
					else
						length = source.length () - start;

					return Variant (source.substr (start, length)).keep ();
				});
			}},
			{"sum",		1,	1,	[] (const vector<const Extractor*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<SumAggregator> ((*slot)++, arguments[0]);
			}},
			{"ucase",	1,	1,	[] (const vector<const Extractor*>& arguments, Int32u*) -> Extractor*
			{
				return new StringUnaryExtractor (arguments[0], [] (const string& argument)
				{
					char* buffer;
					Variant upper;

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
				return new ReduceCompositeExtractor<VarianceAggregator> ((*slot)++, arguments[0]);
			}},
			{0, 0, 0, 0}
		};
	}
}

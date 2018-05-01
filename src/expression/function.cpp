
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
#include "../arithmetic/extractor/binary.hpp"
#include "../arithmetic/extractor/composite/constant.hpp"
#include "../arithmetic/extractor/composite/reduce.hpp"
#include "../arithmetic/extractor/if.hpp"
#include "../arithmetic/extractor/unary.hpp"
#include "../arithmetic/extractor/vector/callback.hpp"
#include "../arithmetic/extractor/vector/lazy.hpp"
#include "wrapper.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Arithmetic;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Expression
	{
		Function const Function::functions[] =
		{
			{"abs",		1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "abs", wrapNumber ([] (Float64 value)
				{
					return Variant (fabs (value));
				}));
			}},
			{"at",		1,	0,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new LazyVectorExtractor (arguments, "at", [] (LazyVectorExtractor::Resolver resolver, Int32u count)
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
			{"avg",		1,	1,	[] (const vector<Extractor const*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<AverageAggregator> ((*slot)++, arguments[0], "avg");
			}},
			{"case",	2,	0,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new LazyVectorExtractor (arguments, "case", [] (LazyVectorExtractor::Resolver resolver, Int32u count)
				{
					Int32u index;
					Variant const& search = resolver (0);

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
			{"ceil",	1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "ceil", wrapNumber ([] (Float64 value)
				{
					return Variant (ceil (value));
				}));
			}},
			{"cmp",		2,	2,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new BinaryExtractor (arguments[0], arguments[1], "cmp", [] (Variant const& lhs, Variant const& rhs)
				{
					return Variant ((Int64s)lhs.compare (rhs));
				});
			}},
			{"count",	0,	0,	[] (const vector<Extractor const*>&, Int32u* slot) -> Extractor*
			{
				return new ConstantCompositeExtractor<CountAggregator> ((*slot)++, Variant::empty, "count");
			}},
			{"default",	1,	2,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, "default", [] (Variant const* values, Int32u count)
				{
					bool test;

					if (values[0].toBoolean (&test) && test)
						return values[0];

					return count > 1 ? values[1] : Variant::empty;
				});
			}},
			{"find",	2,	3,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, "find", [] (Variant const* values, Int32u count)
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

						start = std::min ((size_t)value, source.length ());
					}
					else
						start = 0;

					position = source.find (search, start);

					return position != string::npos ? Variant ((Int64u)position) : Variant::empty;
				});
			}},
			{"first",	1,	1,	[] (const vector<Extractor const*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<FirstAggregator> ((*slot)++, arguments[0], "first");
			}},
			{"floor",	1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "floor", wrapNumber ([] (Float64 value)
				{
					return Variant (floor (value));
				}));
			}},
			{"if",		2,	3,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				if (arguments.size () == 3)
					return new IfExtractor (arguments[0], arguments[1], arguments[2]);
				else
					return new IfExtractor (arguments[0], arguments[1]);
			}},
			{"in",		1,	0,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, "in", [] (Variant const* values, Int32u count)
				{
					Variant const* search;

					search = values++;

					for (; count-- > 1; ++values)
					{
						if (search->compare (*values) == 0)
							return Variant (true);
					}

					return Variant (false);
				});
			}},
			{"last",	1,	1,	[] (const vector<Extractor const*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<LastAggregator> ((*slot)++, arguments[0], "last");
			}},
			{"lcase",	1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "lcase", wrapString ([] (const string& argument)
				{
					char* buffer;
					Variant lower;

					buffer = new char[argument.length ()];

					for (auto i = argument.length (); i-- > 0; )
						buffer[i] = tolower (argument[i]);

					lower = Variant (buffer, argument.length ()).keep ();

					delete [] buffer;

					return lower;
				}));
			}},
			{"len",		1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "len", wrapString ([] (const string& argument)
				{
					return Variant ((Int64u)argument.length ());
				}));
			}},
			{"log",		1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "log", wrapNumber ([] (Float64 value)
				{
					if (value <= 0)
						return Variant::empty;

					return Variant (log (value));
				}));
			}},
			{"max",		1,	0,	[] (const vector<Extractor const*>& arguments, Int32u* slot) -> Extractor*
			{
				if (arguments.size () == 1)
					return new ReduceCompositeExtractor<MaxAggregator> ((*slot)++, arguments[0], "max");

				return new CallbackVectorExtractor (arguments, "max", [] (Variant const* values, Int32u count)
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
			{"min",		1,	0,	[] (const vector<Extractor const*>& arguments, Int32u* slot) -> Extractor*
			{
				if (arguments.size () == 1)
					return new ReduceCompositeExtractor<MinAggregator> ((*slot)++, arguments[0], "min");

				return new CallbackVectorExtractor (arguments, "min", [] (Variant const* values, Int32u count)
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
			{"pow",		2,	2,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new BinaryExtractor (arguments[0], arguments[1], "pow", wrapNumber ([] (Float64 base, Float64 exponent)
				{
					return Variant (pow (base, exponent));
				}));
			}},
			{"round",	1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "round", wrapNumber ([] (Float64 value)
				{
					return Variant (round (value));
				}));
			}},
			{"slice",	2,	3,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new CallbackVectorExtractor (arguments, "slice", [] (Variant const* values, Int32u count)
				{
					Int32u length;
					string source;
					Int32u start;
					Float64 value;

					if (!values[0].toString (&source) || !values[1].toNumber (&value))
						return Variant::empty;

					if (value < 0)
						start = std::min (source.length () + (size_t)value, source.length ());
					else
						start = std::min ((size_t)value, source.length ());

					if (count > 2)
					{
						if (!values[2].toNumber (&value) || value < 0)
							return Variant::empty;

						length = std::min ((size_t)value, source.length () - start);
					}
					else
						length = source.length () - start;

					return Variant (source.substr (start, length)).keep ();
				});
			}},
			{"sum",		1,	1,	[] (const vector<Extractor const*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<SumAggregator> ((*slot)++, arguments[0], "sum");
			}},
			{"type",	1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "type", [] (Variant const& argument)
				{
					switch (argument.getType ())
					{
						case Variant::Type::BOOLEAN:
							return Variant ("boolean", 7);

						case Variant::Type::NUMBER:
							return Variant ("number", 6);

						case Variant::Type::STRING:
							return Variant ("string", 6);

						default:
							return Variant ("none", 4);
					}
				});
			}},
			{"ucase",	1,	1,	[] (const vector<Extractor const*>& arguments, Int32u*) -> Extractor*
			{
				return new UnaryExtractor (arguments[0], "ucase", wrapString ([] (const string& argument)
				{
					char* buffer;
					Variant upper;

					buffer = new char[argument.length ()];

					for (auto i = argument.length (); i-- > 0; )
						buffer[i] = toupper (argument[i]);

					upper = Variant (buffer, argument.length ()).keep ();

					delete [] buffer;

					return upper;
				}));
			}},
			{"var",		1,	1,	[] (const vector<Extractor const*>& arguments, Int32u* slot) -> Extractor*
			{
				return new ReduceCompositeExtractor<VarianceAggregator> ((*slot)++, arguments[0], "var");
			}},
			{0, 0, 0, 0}
		};
	}
}

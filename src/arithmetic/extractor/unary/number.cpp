
#include "number.hpp"

using namespace Glay;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		NumberUnaryExtractor::NumberUnaryExtractor (const Extractor* operand, const string& prefix, Callback callback) :
			UnaryExtractor (operand, prefix),
			callback (callback)
		{
		}

		Variant NumberUnaryExtractor::evaluate (const Variant& argument) const
		{
			Float64 value;

			if (argument.toNumber (&value))
				return this->callback (value);

			return Variant::empty;
		}
	}
}

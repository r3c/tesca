
#include "number.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		NumberUnaryExtractor::NumberUnaryExtractor (const Extractor* source, Callback callback) :
			UnaryExtractor (source),
			callback (callback)
		{
		}

		Variant	NumberUnaryExtractor::evaluate (const Variant& argument) const
		{
			Float64	value;

			if (argument.toNumber (&value))
				return this->callback (value);

			return Variant::empty;
		}
	}
}

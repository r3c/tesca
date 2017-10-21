
#include "boolean.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		BooleanUnaryExtractor::BooleanUnaryExtractor (const Extractor* source, Callback callback) :
			UnaryExtractor (source),
			callback (callback)
		{
		}

		Variant BooleanUnaryExtractor::evaluate (const Variant& argument) const
		{
			bool value;

			if (argument.toBoolean (&value))
				return this->callback (value);

			return Variant::empty;
		}
	}
}

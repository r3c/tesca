
#include "boolean.hpp"

using namespace Glay;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		BooleanUnaryExtractor::BooleanUnaryExtractor (const Extractor* operand, const string& prefix, Callback callback) :
			UnaryExtractor (operand, prefix),
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

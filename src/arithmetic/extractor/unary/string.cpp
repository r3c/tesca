
#include "string.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		StringUnaryExtractor::StringUnaryExtractor (const Extractor* source, Callback callback) :
			UnaryExtractor (source),
			callback (callback)
		{
		}

		Variant StringUnaryExtractor::evaluate (const Variant& argument) const
		{
			string value;

			if (argument.toString (&value))
				return this->callback (value);

			return Variant::empty;
		}
	}
}

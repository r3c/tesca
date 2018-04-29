
#include "string.hpp"

using namespace Glay;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		StringUnaryExtractor::StringUnaryExtractor (const Extractor* source, const string& prefix, Callback callback) :
			UnaryExtractor (source, prefix),
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

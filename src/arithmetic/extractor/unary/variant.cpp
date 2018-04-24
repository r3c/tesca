#include "variant.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		VariantUnaryExtractor::VariantUnaryExtractor (const Extractor* source, Callback callback) :
			UnaryExtractor (source),
			callback (callback)
		{
		}

		Variant VariantUnaryExtractor::evaluate (const Variant& argument) const
		{
            return this->callback (argument);
		}
	}
}

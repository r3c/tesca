#include "variant.hpp"

using namespace Glay;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		VariantUnaryExtractor::VariantUnaryExtractor (const Extractor* operand, const string& prefix, Callback callback) :
			UnaryExtractor (operand, prefix),
			callback (callback)
		{
		}

		Variant VariantUnaryExtractor::evaluate (const Variant& argument) const
		{
            return this->callback (argument);
		}
	}
}

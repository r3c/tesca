
#include "constant.hpp"

using namespace Glay;
using namespace Glay::System;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

namespace Tesca
{
	namespace Arithmetic
	{
		ConstantExtractor::ConstantExtractor (Variant const& value) :
			value (value)
		{
			this->value.keep ();
		}

		string ConstantExtractor::createName (Int32u slot) const
		{
			string name;

			if (this->value.toString (&name))
				return name;

			char buffer[32];

			return string (buffer, Convert::toString (buffer, sizeof (buffer) / sizeof (*buffer), slot));
		}

		Int32u ConstantExtractor::getFlags () const
		{
			return COMPOSITE | SCALAR;
		}

		Variant ConstantExtractor::collect (Aggregator const* const*) const
		{
			return this->value;
		}

		Variant ConstantExtractor::extract (Row const&) const
		{
			return this->value;
		}
	}
}


#ifndef __TESCA_EXPRESSION_WRAPPER_HPP
#define __TESCA_EXPRESSION_WRAPPER_HPP

#include <functional>
#include <string>
#include "../storage/variant.hpp"

namespace Tesca
{
	namespace Expression
	{
		std::function<Storage::Variant (const Storage::Variant&)> booleanUnary (std::function<Storage::Variant (bool)>);
		std::function<Storage::Variant (const Storage::Variant&)> numberUnary (std::function<Storage::Variant (Glay::Float64)>);
		std::function<Storage::Variant (const Storage::Variant&)> stringUnary (std::function<Storage::Variant (const std::string&)>);
	}
}

#endif
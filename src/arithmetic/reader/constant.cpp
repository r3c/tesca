
#include "constant.hpp"

namespace	Tesca
{
	ConstantReader::ConstantReader (const Variant& constant) :
		constant (constant)
	{
	}

	Variant	ConstantReader::read (const Row&) const
	{
		return this->constant;
	}
}

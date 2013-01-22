
#include "constant.hpp"

namespace	Tesca
{
	ConstantColumn::ConstantColumn (const Value& value) :
		constant (value.clone ())
	{
	}

	ConstantColumn::~ConstantColumn ()
	{
		delete this->constant;
	}

	const Value&	ConstantColumn::read (const Row&)
	{
		return *this->constant;
	}
}

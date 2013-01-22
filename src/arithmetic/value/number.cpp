
#include "number.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	NumberValue::NumberValue (Float64 value) :
		value (value)
	{
	}

	NumberValue&	NumberValue::operator = (const NumberValue& other)
	{
		this->value = other.value;

		return *this;
	}

	Value::ContentType	NumberValue::getType () const
	{
		return ContentType::NUMBER;
	}

	Value*	NumberValue::clone () const
	{
		return new NumberValue (this->value);
	}

	bool	NumberValue::toBoolean (bool* output) const
	{
		if (output != 0)
			*output = this->value != 0;

		return true;
	}

	bool	NumberValue::toNumber (Float64* output) const
	{
		if (output != 0)
			*output = this->value;

		return true;
	}

	bool	NumberValue::toString (string* output) const
	{
		if (output != 0)
			*output = this->value;

		return true;
	}
}

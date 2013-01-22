
#include "boolean.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	BooleanValue::BooleanValue (bool value) :
		value (value)
	{
	}

	BooleanValue&	BooleanValue::operator = (const BooleanValue& other)
	{
		this->value = other.value;

		return *this;
	}

	Value::ContentType	BooleanValue::getType () const
	{
		return ContentType::BOOLEAN;
	}

	Value*	BooleanValue::clone () const
	{
		return new BooleanValue (this->value);
	}

	bool	BooleanValue::toBoolean (bool* output) const
	{
		if (output != 0)
			*output = this->value;

		return true;
	}

	bool	BooleanValue::toNumber (Float64* output) const
	{
		if (output != 0)
			*output = this->value ? 1 : 0;

		return true;
	}

	bool	BooleanValue::toString (string* output) const
	{
		if (output != 0)
			*output = this->value ? "true" : "false";

		return true;
	}
}

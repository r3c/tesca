
#include "string.hpp"

#include <sstream>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	StringValue::StringValue (const std::string& value) :
		value (value)
	{
	}

	StringValue::StringValue (const char* value) :
		value (value)
	{
	}

	StringValue&	StringValue::operator = (const StringValue& other)
	{
		this->value = other.value;

		return *this;
	}

	Value::ContentType	StringValue::getType () const
	{
		return ContentType::STRING;
	}

	Value*	StringValue::clone () const
	{
		return new StringValue (this->value);
	}

	bool	StringValue::toBoolean (bool* output) const
	{
		if (output != 0)
			*output = !this->value.empty ();

		return true;
	}

	bool	StringValue::toNumber (Float64* output) const
	{
		stringstream	stream (this->value);
		Float64			number;

		stream >> number;

		if (stream.fail ())
			return false;

		if (output != 0)
			*output = number;

		return true;
	}

	bool	StringValue::toString (string* output) const
	{
		if (output != 0)
			*output = this->value;

		return true;
	}
}

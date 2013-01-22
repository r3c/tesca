
#include "value.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	Value::Value ()
	{
	}

	bool	operator == (const Value& lhs, const Value& rhs)
	{
		bool	boolean1;
		bool	boolean2;
		Float64	number1;
		Float64	number2;
		string	string1;
		string	string2;

		switch (lhs.getType ())
		{
			case Value::ContentType::BOOLEAN:
				return lhs.toBoolean (&boolean1) && rhs.toBoolean (&boolean2) && boolean1 == boolean2;

			case Value::ContentType::NUMBER:
				return lhs.toNumber (&number1) && rhs.toNumber (&number2) && number1 == number2;

			case Value::ContentType::STRING:
				return lhs.toString (&string1) && rhs.toString (&string2) && string1 == string2;

			case Value::ContentType::NONE:
				return rhs.getType () == Value::ContentType::NONE;
		}

		return lhs.getType () == rhs.getType ();
	}

	bool	operator != (const Value& lhs, const Value& rhs)
	{
		return !operator == (lhs, rhs);
	}

	bool	operator < (const Value& lhs, const Value& rhs)
	{
		bool	boolean1;
		bool	boolean2;
		Float64	number1;
		Float64	number2;
		string	string1;
		string	string2;

		switch (lhs.getType ())
		{
			case Value::ContentType::BOOLEAN:
				if (lhs.toBoolean (&boolean1) && rhs.toBoolean (&boolean2))
					return boolean1 < boolean2;

				break;

			case Value::ContentType::NUMBER:
				if (lhs.toNumber (&number1) && rhs.toNumber (&number2))
					return number1 < number2;

				break;

			case Value::ContentType::STRING:
				if (lhs.toString (&string1) && rhs.toString (&string2))
					return string1 < string2;

				break;

			case Value::ContentType::NONE:
				return rhs.getType () > Value::ContentType::NONE;
		}

		return lhs.getType () < rhs.getType ();
	}
}

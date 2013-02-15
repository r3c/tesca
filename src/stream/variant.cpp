
#include "variant.hpp"

#include <sstream>
#include <string.h>

using namespace std;
using namespace Glay;

namespace	Tesca
{
	const Variant	Variant::empty = Variant ();

	Variant::Variant (const Variant& other) :
		type (Variant::NONE)
	{
		*this = other;
	}

	Variant::Variant (bool boolean) :
		type (Variant::BOOLEAN)
	{
		this->value.boolean = boolean;
	}

	Variant::Variant (Float64 number) :
		type (Variant::NUMBER)
	{
		this->value.number = number;
	}

	Variant::Variant (Int32s integer) :
		type (Variant::NUMBER)
	{
		this->value.number = integer;
	}

	Variant::Variant (const string& string) :
		type (Variant::STRING)
	{
		char*	buffer;
		size_t	size;

		size = string.length () + 1;
		buffer = new char[size];

		memcpy (buffer, string.c_str (), size * sizeof (*buffer));

		this->share = new Int32u (1);
		this->value.string = buffer;
	}

	Variant::Variant (const char* string) :
		type (Variant::STRING)
	{
		char*	buffer;
		size_t	size;

		size = strlen (string) + 1;
		buffer = new char[size];

		memcpy (buffer, string, size * sizeof (*buffer));

		this->share = new Int32u (1);
		this->value.string = buffer;
	}

	Variant::Variant () :
		type (Variant::NONE)
	{
	}

	Variant::~Variant ()
	{
		this->clear ();
	}

	Variant&	Variant::operator = (const Variant& other)
	{
		if (this != &other)
		{
			this->clear ();

			switch (other.type)
			{
				case Variant::BOOLEAN:
					this->value.boolean = other.value.boolean;

					break;

				case Variant::NUMBER:
					this->value.number = other.value.number;

					break;

				case Variant::STRING:
					this->share = other.share;
					this->value.string = other.value.string;

					++*this->share;

					break;

				default:
					break;
			}

			this->type = other.type;
		}

		return *this;
	}

	void	Variant::clear ()
	{
		switch (this->type)
		{
			case Variant::STRING:
				if (--*this->share < 1)
				{
					delete this->share;
					delete [] this->value.string;
				}

				break;

			default:
				break;
		}

		this->type = Variant::NONE;
	}

	Variant::Type	Variant::getType () const
	{
		return this->type;
	}

	bool	Variant::toBoolean (bool* output) const
	{
		switch (this->type)
		{
			case Variant::BOOLEAN:
				*output = this->value.boolean;

				return true;

			case Variant::NUMBER:
				*output = this->value.number != 0;

				return true;

			case Variant::STRING:
				*output = this->value.string[0] != '\0';

				return true;

			default:
				return false;
		}
	}

	bool	Variant::toNumber (Float64* output) const
	{
		Float64			number;
		stringstream	stream;

		switch (this->type)
		{
			case Variant::BOOLEAN:
				*output = this->value.boolean ? 1 : 0;

				return true;

			case Variant::NUMBER:
				*output = this->value.number;

				return true;

			case Variant::STRING:
				stream << this->value.string;
				stream >> number;

				if (stream.fail ())
					return false;

				*output = number;

				return true;

			default:
				return false;
		}
	}

	bool	Variant::toString (string* output) const
	{
		ostringstream	stream;

		switch (this->type)
		{
			case Variant::BOOLEAN:
				*output = this->value.boolean ? "true" : "false";

				return true;

			case Variant::NUMBER:
				stream << this->value.number;

				*output = stream.str ();

				return true;

			case Variant::STRING:
				*output = this->value.string;

				return true;

			default:
				return false;
		}
	}

	bool	operator == (const Variant& lhs, const Variant& rhs)
	{
		bool	boolean1;
		bool	boolean2;
		Float64	number1;
		Float64	number2;
		string	string1;
		string	string2;

		switch (lhs.getType ())
		{
			case Variant::BOOLEAN:
				return lhs.toBoolean (&boolean1) && rhs.toBoolean (&boolean2) && boolean1 == boolean2;

			case Variant::NUMBER:
				return lhs.toNumber (&number1) && rhs.toNumber (&number2) && number1 == number2;

			case Variant::STRING:
				return lhs.toString (&string1) && rhs.toString (&string2) && string1 == string2;

			case Variant::NONE:
				return rhs.getType () == Variant::NONE;
		}

		return lhs.getType () == rhs.getType ();
	}

	bool	operator != (const Variant& lhs, const Variant& rhs)
	{
		return !operator == (lhs, rhs);
	}

	bool	operator < (const Variant& lhs, const Variant& rhs)
	{
		bool	boolean1;
		bool	boolean2;
		Float64	number1;
		Float64	number2;
		string	string1;
		string	string2;

		switch (lhs.getType ())
		{
			case Variant::BOOLEAN:
				if (lhs.toBoolean (&boolean1) && rhs.toBoolean (&boolean2))
					return boolean1 < boolean2;

				break;

			case Variant::NUMBER:
				if (lhs.toNumber (&number1) && rhs.toNumber (&number2))
					return number1 < number2;

				break;

			case Variant::STRING:
				if (lhs.toString (&string1) && rhs.toString (&string2))
					return string1 < string2;

				break;

			default:
				break;
		}

		return lhs.getType () < rhs.getType ();
	}

	ostream&	operator << (ostream& stream, const Variant& value)
	{
		bool	asBoolean;
		Float64	asNumber;
		string	asString;

		switch (value.getType ())
		{
			case Tesca::Variant::BOOLEAN:
				if (value.toBoolean (&asBoolean))
					stream << (asBoolean ? "true" : "false");
				else
					stream << "!";

				break;

			case Tesca::Variant::NUMBER:
				if (value.toNumber (&asNumber))
					stream << asNumber;
				else
					stream << "!";

				break;

			case Tesca::Variant::STRING:
				if (value.toString (&asString))
					stream << asString;
				else
					stream << "!";

				break;

			case Tesca::Variant::NONE:
				stream << "void";

				break;

			default:
				stream << "?";

				break;
		}

		return stream;
	}
}

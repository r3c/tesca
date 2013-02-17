
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
		this->reset ();
	}

	Variant&	Variant::operator = (const Variant& other)
	{
		if (this != &other)
		{
			this->reset ();

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

	Variant::Type	Variant::getType () const
	{
		return this->type;
	}

	Int32s	Variant::compare (const Variant& other) const
	{
		bool	boolean1;
		bool	boolean2;
		Float64	number1;
		Float64	number2;
		string	string1;
		string	string2;

		switch (this->type)
		{
			case Variant::BOOLEAN:
				if (this->toBoolean (&boolean1) && other.toBoolean (&boolean2))
				{
					if (boolean1 < boolean2)
						return -1;
					else if (boolean1 > boolean2)
						return 1;
					else
						return 0;
				}

				break;

			case Variant::NUMBER:
				if (this->toNumber (&number1) && other.toNumber (&number2))
				{
					if (number1 < number2)
						return -1;
					else if (number1 > number2)
						return 1;
					else
						return 0;
				}

				break;

			case Variant::STRING:
				if (this->toString (&string1) && other.toString (&string2))
					return string1.compare (string2);

				break;

			default:
				break;
		}

		if (this->type < other.type)
			return -1;
		else if (this->type > other.type)
			return 1;
		else
			return 0;
	}

	void	Variant::reset ()
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
		return lhs.compare (rhs) == 0;
	}

	bool	operator != (const Variant& lhs, const Variant& rhs)
	{
		return lhs.compare (rhs) != 0;
	}

	bool	operator <= (const Variant& lhs, const Variant& rhs)
	{
		return lhs.compare (rhs) <= 0;
	}

	bool	operator < (const Variant& lhs, const Variant& rhs)
	{
		return lhs.compare (rhs) < 0;
	}

	bool	operator >= (const Variant& lhs, const Variant& rhs)
	{
		return lhs.compare (rhs) >= 0;
	}
	
	bool	operator > (const Variant& lhs, const Variant& rhs)
	{
		return lhs.compare (rhs) > 0;
	}
}

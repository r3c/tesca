
#include "variant.hpp"

#include <cstring>

using namespace std;
using namespace Glay;
using namespace Glay::System;

namespace
{
	template<typename T>
	static inline Int32s	typeCompare (T a, T b)
	{
		if (a < b)
			return -1;
		else if (a > b)
			return 1;

		return 0;
	}
}

namespace	Tesca
{
	namespace	Storage
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
			this->content.boolean = boolean;
		}

		Variant::Variant (Float64 number) :
			type (Variant::NUMBER)
		{
			this->content.number = number;
		}

		Variant::Variant (Int32s integer) :
			type (Variant::NUMBER)
		{
			this->content.number = integer;
		}

		Variant::Variant (Int32u integer) :
			type (Variant::NUMBER)
		{
			this->content.number = integer;
		}

		Variant::Variant (const char* buffer, Int32u length) :
			share (0),
			type (Variant::STRING)
		{
			this->content.string.buffer = buffer;
			this->content.string.length = length;
		}

		Variant::Variant (const string& string) :
			share (0),
			type (Variant::STRING)
		{
			this->content.string.buffer = string.c_str ();
			this->content.string.length = string.length ();
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
						this->content.boolean = other.content.boolean;

						break;

					case Variant::NUMBER:
						this->content.number = other.content.number;

						break;

					case Variant::STRING:
						if (other.share != 0)
							++*other.share;

						this->content.string = other.content.string;
						this->share = other.share;

						break;

					default:
						break;
				}

				this->type = other.type;
			}

			return *this;
		}

		Int32s	Variant::compare (const Variant& other) const
		{
			bool		boolean1;
			bool		boolean2;
			const char*	buffer1;
			const char*	buffer2;
			Int32u		compare;
			Int32u		length1;
			Int32u		length2;
			Float64		number1;
			Float64		number2;
			string		string1;
			string		string2;

			switch (min (this->type, other.type))
			{
				case Variant::BOOLEAN:
					if (this->type != other.type)
					{
						if (!this->toBoolean (&boolean1) || !other.toBoolean (&boolean2))
							break;
					}
					else
					{
						boolean1 = this->content.boolean;
						boolean2 = other.content.boolean;
					}

					return typeCompare (boolean1, boolean2);

				case Variant::NUMBER:
					if (this->type != other.type)
					{
						if (!this->toNumber (&number1) || !other.toNumber (&number2))
							break;
					}
					else
					{
						number1 = this->content.number;
						number2 = other.content.number;
					}

					return typeCompare (number1, number2);

				case Variant::STRING:
					if (this->type != other.type)
					{
						if (!this->toString (&string1) || !other.toString (&string2))
							break;

						buffer1 = string1.c_str ();
						buffer2 = string2.c_str ();
						length1 = string1.length ();
						length2 = string2.length ();
					}
					else
					{
						buffer1 = this->content.string.buffer;
						buffer2 = other.content.string.buffer;
						length1 = this->content.string.length;
						length2 = other.content.string.length;
					}

					compare = memcmp (buffer1, buffer2, min (length1, length2));

					if (compare != 0)
						return compare;

					return typeCompare (length1, length2);

				default:
					break;
			}

			return typeCompare (this->type, other.type);
		}

		Variant&	Variant::keep ()
		{
			Int32u	length;
			char*	target;

			switch (this->type)
			{
				case Variant::STRING:
					if (this->share != 0)
					{
						if (*this->share <= 1)
							break;

						--*this->share;
					}

					length = this->content.string.length;
					target = static_cast<char*> (malloc (length * sizeof (*target)));

					memcpy (target, this->content.string.buffer, length * sizeof (*target));

					this->content.string.buffer = target;
					this->share = static_cast<Int32u*> (malloc (sizeof (*this->share)));

					*this->share = 1;

					break;

				default:
					break;
			}

			return *this;
		}

		void	Variant::reset ()
		{
			switch (this->type)
			{
				case Variant::STRING:
					if (this->share != 0 && --*this->share == 0)
					{
						free (const_cast<char*> (this->content.string.buffer));
						free (this->share);
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
					*output = this->content.boolean;

					return true;

				case Variant::NUMBER:
					*output = this->content.number != 0;

					return true;

				case Variant::STRING:
					*output = this->content.string.length > 0;

					return true;

				default:
					return false;
			}
		}

		bool	Variant::toNumber (Float64* output) const
		{
			switch (this->type)
			{
				case Variant::BOOLEAN:
					*output = this->content.boolean ? 1 : 0;

					return true;

				case Variant::NUMBER:
					*output = this->content.number;

					return true;

				case Variant::STRING:
					return Convert::toFloat64 (output, this->content.string.buffer, this->content.string.length);

				default:
					return false;
			}
		}

		bool	Variant::toString (string* output) const
		{
			char	buffer[64];
			Int32u	length;

			switch (this->type)
			{
				case Variant::BOOLEAN:
					*output = this->content.boolean ? "true" : "false";

					return true;

				case Variant::NUMBER:
					length = Convert::toString (buffer, sizeof (buffer) / sizeof (*buffer), this->content.number);

					if (length == 0)
						return false;

					*output = string (buffer, length);

					return true;

				case Variant::STRING:
					*output = string (this->content.string.buffer, this->content.string.length);

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
}


#include "bucket.hpp"

#include "value/void.hpp"

using namespace Glay;

namespace	Tesca
{
	Bucket::Bucket (const Bucket& other) :
		size (other.size)
	{
		this->buffer = new const Value*[this->size];

		memcpy (this->buffer, other.buffer, this->size * sizeof (*this->buffer));
	}

	Bucket::Bucket (Int32u size) :
		size (size)
	{
		this->buffer = new const Value*[size];

		memset (this->buffer, 0, size * sizeof (*this->buffer));
	}

	Bucket::~Bucket ()
	{
		delete [] this->buffer;
	}

	const Value&	Bucket::operator [] (Int32u index) const
	{
		if (this->buffer[index] != 0)
			return *this->buffer[index];

		return VoidValue::instance;
	}

	Int16s	Bucket::compare (const Bucket& other) const
	{
		if (this->length () < other.length ())
			return -1;
		else if (this->length () > other.length ())
			return 1;

		for (Int32u index = 0; index < this->length (); ++index)
		{
			const Value&	lhs = (*this)[index];
			const Value&	rhs = other[index];

			if (lhs < rhs)
				return -1;
			else if (rhs < lhs)
				return 1;
		}

		return 0;
	}

	Int32u	Bucket::length () const
	{
		return this->size;
	}

	void	Bucket::set (Int32u index, const Value* value)
	{
		this->buffer[index] = value;
	}

	bool	operator < (const Bucket& lhs, const Bucket& rhs)
	{
		return lhs.compare (rhs) < 0;
	}
}

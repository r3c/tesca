
#include "bucket.hpp"

using namespace Glay;

namespace	Tesca
{
	Bucket::Bucket (const Bucket& other) :
		size (other.size)
	{
		Variant*	buffer;

		buffer = new Variant[other.size];

		for (Int32u i = other.size; i-- > 0; )
			buffer[i] = other.buffer[i];

		this->buffer = buffer;
	}

	Bucket::Bucket (Int32u size) :
		size (size)
	{
		this->buffer = new Variant[size];
	}

	Bucket::~Bucket ()
	{
		delete [] this->buffer;
	}

	const Variant&	Bucket::operator [] (Int32u index) const
	{
		return this->buffer[index];
	}

	Int16s	Bucket::compare (const Bucket& other) const
	{
		if (this->length () < other.length ())
			return -1;
		else if (this->length () > other.length ())
			return 1;

		for (Int32u index = 0; index < this->length (); ++index)
		{
			const Variant&	lhs = (*this)[index];
			const Variant&	rhs = other[index];

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

	void	Bucket::set (Int32u index, const Variant& value)
	{
		this->buffer[index] = value;
	}

	bool	operator < (const Bucket& lhs, const Bucket& rhs)
	{
		return lhs.compare (rhs) < 0;
	}
}


#include "bucket.hpp"

using namespace Glay;
using namespace Tesca::Stream;

namespace	Tesca
{
	Bucket::Bucket (const Bucket& other) :
		length (other.length)
	{
		Variant*	buffer;

		buffer = new Variant[other.length];

		for (Int32u i = other.length; i-- > 0; )
			buffer[i] = other.buffer[i];

		this->buffer = buffer;
	}

	Bucket::Bucket (Int32u length) :
		length (length)
	{
		this->buffer = new Variant[length];
	}

	Bucket::~Bucket ()
	{
		delete [] this->buffer;
	}

	const Variant&	Bucket::operator [] (Int32u index) const
	{
		return this->buffer[index];
	}

	Int32u	Bucket::getLength () const
	{
		return this->length;
	}

	Int16s	Bucket::compare (const Bucket& other) const
	{
		if (this->length < other.length)
			return -1;
		else if (this->length > other.length)
			return 1;

		for (Int32u index = 0; index < this->length; ++index)
		{
			const Variant&	lhs = this->buffer[index];
			const Variant&	rhs = other.buffer[index];

			if (lhs < rhs)
				return -1;
			else if (rhs < lhs)
				return 1;
		}

		return 0;
	}

	Bucket&	Bucket::keep ()
	{
		for (Int32u index = this->length; index-- > 0; )
			this->buffer[index].keep ();

		return *this;
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

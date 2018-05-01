
#include "bucket.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		Bucket::Bucket (Bucket const& other) :
			length (other.length)
		{
			Variant* buffer;

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

		Variant const& Bucket::operator [] (Int32u index) const
		{
			return this->buffer[index];
		}

		Int32u Bucket::getLength () const
		{
			return this->length;
		}

		Int16s Bucket::compare (Bucket const& other) const
		{
			if (this->length < other.length)
				return -1;
			else if (this->length > other.length)
				return 1;

			for (Int32u index = 0; index < this->length; ++index)
			{
				Variant const& lhs = this->buffer[index];
				Variant const& rhs = other.buffer[index];

				if (lhs < rhs)
					return -1;
				else if (rhs < lhs)
					return 1;
			}

			return 0;
		}

		Bucket& Bucket::keep ()
		{
			for (Int32u index = this->length; index-- > 0; )
				this->buffer[index].keep ();

			return *this;
		}

		void Bucket::set (Int32u index, Variant const& value)
		{
			this->buffer[index] = value;
		}

		bool operator < (Bucket const& lhs, Bucket const& rhs)
		{
			return lhs.compare (rhs) < 0;
		}
	}
}

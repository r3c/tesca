
#include "array.hpp"

using namespace Glay;

namespace	Tesca
{
	ArrayRow::ArrayRow (Int32u length) :
		length (length),
		values (new Variant[length])
	{
	}

	ArrayRow::~ArrayRow ()
	{
		delete [] this->values;
	}

	const Variant&	ArrayRow::operator [] (Int32u key) const
	{
		if (key < this->length)
			return this->values[key];

		return Variant::empty;
	}

	Int32u	ArrayRow::getLength () const
	{
		return this->length;
	}

	void	ArrayRow::clear ()
	{
		for (auto i = this->length; i-- > 0; )
			this->values[i] = Variant::empty;
	}

	bool	ArrayRow::set (Int32u key, const Variant& value)
	{
		if (key >= this->length)
			return false;

		this->values[key] = value;

		return true;
	}
}

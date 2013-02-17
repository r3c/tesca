
#include "array.hpp"

using namespace Glay;

namespace	Tesca
{
	ArrayRow::ArrayRow (Int32u size) :
		size (size),
		values (new Variant[size])
	{
	}

	ArrayRow::~ArrayRow ()
	{
		delete [] this->values;
	}

	const Variant&	ArrayRow::operator [] (Int32u key) const
	{
		if (key < this->size)
			return this->values[key];

		return Variant::empty;
	}

	Variant&	ArrayRow::operator [] (Int32u key)
	{
		if (key < this->size)
			return this->values[key];

		return this->dummy;
	}

	void	ArrayRow::clear ()
	{
		for (auto i = this->size; i-- > 0; )
			this->values[i] = Variant::empty;
	}
}

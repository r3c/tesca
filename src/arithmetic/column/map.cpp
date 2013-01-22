
#include "map.hpp"

#include "../value/void.hpp"

namespace	Tesca
{
	MapColumn::MapColumn (Column* source) :
		result (&VoidValue::instance),
		source (source)
	{
	}

	void	MapColumn::update (const Row& row)
	{
		this->source->update (row);

		this->result = &this->map (this->source->value ());
	}

	const Value&	MapColumn::value () const
	{
		return *this->result;
	}
}

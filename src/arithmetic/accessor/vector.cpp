
#include "vector.hpp"

using namespace std;

namespace	Tesca
{
	VectorAccessor::VectorAccessor (const Accessors& accessors) :
		accessors (accessors)
	{
	}

	Variant	VectorAccessor::read (const Row& row) const
	{
		Values	values (this->accessors.size ());

		for (auto i = this->accessors.begin (); i != this->accessors.end (); ++i)
			values.push_back ((*i)->read (row));

		return this->evaluate (values);
	}
}

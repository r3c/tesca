
#include "vector.hpp"

using namespace std;
using namespace Tesca::Provision;

namespace	Tesca
{
	namespace	Arithmetic
	{
		VectorAccessor::VectorAccessor (const vector<const Accessor*>& accessors) :
			accessors (new const Accessor*[accessors.size ()]),
			length (accessors.size ())
		{
			for (auto i = accessors.size (); i-- > 0; )
				this->accessors[i] = accessors[i];
		}

		VectorAccessor::~VectorAccessor ()
		{
			delete [] this->accessors;
		}

		Variant	VectorAccessor::read (const Row& row) const
		{
			Variant	values[this->length];

			for (auto i = this->length; i-- > 0; )
				values[i] = this->accessors[i]->read (row);

			return this->evaluate (values, this->length);
		}
	}
}

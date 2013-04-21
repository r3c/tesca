
#include "callback.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Arithmetic
	{
		CallbackVectorAccessor::CallbackVectorAccessor (const vector<const Accessor*>& accessors, Callback callback) :
			VectorAccessor (accessors),
			callback (callback)
		{
		}

		Variant	CallbackVectorAccessor::evaluate (const Variant* values, Int32u length) const
		{
			return this->callback (values, length);
		}
	}
}

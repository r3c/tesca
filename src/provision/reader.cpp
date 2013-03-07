
#include "reader.hpp"

using namespace Glay;

namespace	Tesca
{
	namespace	Provision
	{
		Reader::Reader () :
			errors (0)
		{
		}

		Reader::~Reader ()
		{
		}

		Int32u	Reader::getErrors () const
		{
			return this->errors;
		}
	}
}

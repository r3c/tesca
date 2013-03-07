
#include "reader.hpp"

using namespace Glay::Design;

namespace	Tesca
{
	namespace	Provision
	{
		Reader::Reader ()
		{
		}

		Reader::~Reader ()
		{
		}

		const Reader::ErrorEvent&	Reader::getError () const
		{
			return this->error;
		}

		Reader::ErrorEvent&	Reader::getError ()
		{
			return this->error;
		}
	}
}

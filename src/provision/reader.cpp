
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

		const Reader::Error&	Reader::getError () const
		{
			return this->error;
		}

		Reader::Error&	Reader::getError ()
		{
			return this->error;
		}
	}
}

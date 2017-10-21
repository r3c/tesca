
#include "reader.hpp"

using namespace Glay;
using namespace Glay::Design;

namespace Tesca
{
	namespace Provision
	{
		Reader::Progress::Progress (Int64u read, Int64u size) :
			read (read),
			size (size)
		{
		}

		Reader::Reader ()
		{
		}

		Reader::~Reader ()
		{
		}

		const Reader::Error& Reader::onError () const
		{
			return this->error;
		}

		Reader::Error& Reader::onError ()
		{
			return this->error;
		}

		const Reader::Read& Reader::onRead () const
		{
			return this->read;
		}

		Reader::Read& Reader::onRead ()
		{
			return this->read;
		}
	}
}

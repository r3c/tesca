
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

		Reader::Error const& Reader::onError () const
		{
			return this->error;
		}

		Reader::Error& Reader::onError ()
		{
			return this->error;
		}

		Reader::Read const& Reader::onRead () const
		{
			return this->read;
		}

		Reader::Read& Reader::onRead ()
		{
			return this->read;
		}
	}
}

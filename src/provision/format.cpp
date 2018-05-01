
#include "format.hpp"

#include "reader/line/csv.hpp"
#include "reader/line/json.hpp"

using namespace Glay;
using namespace Glay::Pipe;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Provision
	{
		Format const Format::formats[] =
		{
			{"csv",		[] (SeekIStream* stream, Lookup const& lookup, Config const& config) -> Reader*
			{
				return new CSVLineReader (stream, lookup, config);
			}},
			{"json",	[] (SeekIStream* stream, Lookup const& lookup, Config const& config) -> Reader*
			{
				return new JSONLineReader (stream, lookup, config);
			}},
			{0, 0}
		};
	}
}

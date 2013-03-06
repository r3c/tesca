
#include "parser.hpp"

#include "reader/line/csv.hpp"
#include "reader/line/json.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	namespace	Provision
	{
		const Parser	Parser::parsers[] =
		{
			{"csv",		[] (Pipe::IStream* stream, const Lookup& lookup, const Config& config) -> Reader*
			{
				return new CSVLineReader (stream, lookup, config);
			}},
			{"json",	[] (Pipe::IStream* stream, const Lookup& lookup, const Config& config) -> Reader*
			{
				return new JSONLineReader (stream, lookup, config);
			}},
			{0, 0}
		};
	}
}

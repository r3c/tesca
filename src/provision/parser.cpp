
#include "parser.hpp"

#include "reader/line/csv.hpp"

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
			{0, 0}
		};
	}
}

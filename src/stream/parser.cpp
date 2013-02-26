
#include "parser.hpp"

#include "reader/line/csv.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	const Parser	Parser::parsers[] =
	{
		{"csv",		[] (Pipe::IStream* stream, const Reader::Fields& fields, const Config& config) -> Reader*
		{
			return new CSVLineReader (stream, fields, config);
		}},
		{0, 0}
	};
}

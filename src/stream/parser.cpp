
#include "parser.hpp"

#include "reader/line/csv.hpp"

using namespace std;
using namespace Glay;

namespace	Tesca
{
	const Parser	Parser::parsers[] =
	{
		{"csv",		[] (Pipe::IStream* stream, const Reader::Fields* fields, const char* /*options*/) -> Reader*
		{
			return new CSVLineReader (stream, fields, false, ',');
		}},
		{0, 0}
	};
}

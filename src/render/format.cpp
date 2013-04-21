
#include "format.hpp"

#include "printer/csv.hpp"
#include "printer/name.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Render
	{
		const Format	Format::formats[] =
		{
			{"csv",		[] (const Config& config) -> Printer*
			{
				return new CSVPrinter (config);
			}},
			{"name",	[] (const Config& config) -> Printer*
			{
				return new NamePrinter (config);
			}},
			{0, 0}
		};
	}
}

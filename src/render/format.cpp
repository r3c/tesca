
#include "format.hpp"

#include "printer/csv.hpp"
#include "printer/name.hpp"
#include "printer/pretty.hpp"

using namespace Glay;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Render
	{
		Format const Format::formats[] =
		{
			{"csv",		[] (Config const& config) -> Printer*
			{
				return new CSVPrinter (config);
			}},
			{"name",	[] (Config const& config) -> Printer*
			{
				return new NamePrinter (config);
			}},
			{"pretty",	[] (Config const& config) -> Printer*
			{
				return new PrettyPrinter (config);
			}},
			{0, 0}
		};
	}
}

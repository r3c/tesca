
#include "csv.hpp"

using namespace Glay::Pipe;
using namespace Tesca::Arithmetic;

namespace	Tesca
{
	namespace	Render
	{
		CSVPrinter::CSVPrinter ()
		{
		}

		CSVPrinter::~CSVPrinter ()
		{
		}

		void	CSVPrinter::print (OStream& stream, const Table&)
		{
			stream.write ("CSV printer not implemented\n", 28);
		}
	}
}

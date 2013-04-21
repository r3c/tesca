
#include "csv.hpp"

#include <string>

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Tesca::Arithmetic;
using namespace Tesca::Storage;

namespace	Tesca
{
	namespace	Render
	{
		CSVPrinter::CSVPrinter (const Config& config)
		{
			this->headers = config.get ("headers", 0);
		}

		CSVPrinter::~CSVPrinter ()
		{
		}

		void	CSVPrinter::print (OStream& stream, const Table& table)
		{
			string	value;
			Int32u	width;

			if (this->headers)
			{
				auto	columns = table.getColumns ();

				for (Int32u i = 0; i < columns.size (); ++i)
				{
					if (i > 0)
						stream.write (",", 1); // FIXME

					stream.write (columns[i]->getIdentifier ().c_str (), columns[i]->getIdentifier ().length ());
				}

				stream.write ("\n", 1); // FIXME
			}

			width = table.getWidth ();

			for (auto row = table.begin (); row != table.end (); ++row)
			{
				auto	slot = row->second;

				for (Int32u i = 0; i < width; ++i)
				{
					if (i > 0)
						stream.write (",", 1); // FIXME

					if ((*slot)->current ().toString (&value))
						stream.write (value.c_str (), value.length ());

					++slot;
				}

				stream.write ("\n", 1); // FIXME
			}
		}
	}
}

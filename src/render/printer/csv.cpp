
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
			this->quote = config.get ("quote", "");
			this->split = config.get ("split", ",");
		}

		CSVPrinter::~CSVPrinter ()
		{
		}

		void	CSVPrinter::print (OStream& stream, const Table& table)
		{
			string			value;
			Int32u			width;
			FormatWriter	writer (stream);

			if (this->headers)
			{
				auto	columns = table.getColumns ();

				for (Int32u i = 0; i < columns.size (); ++i)
				{
					if (i > 0)
						writer.write (this->split);

					writer
						.write (this->quote)
						.write (columns[i]->getIdentifier ())
						.write (this->quote);
				}

				writer.write ("\n");
			}

			width = table.getWidth ();

			for (auto row = table.begin (); row != table.end (); ++row)
			{
				auto	slot = row->second;

				for (Int32u i = 0; i < width; ++i)
				{
					if (i > 0)
						writer.write (this->split);

					if ((*slot)->current ().toString (&value))
					{
						writer
							.write (this->quote)
							.write (value)
							.write (this->quote);
					}

					++slot;
				}

				writer.write ("\n");
			}
		}
	}
}

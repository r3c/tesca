
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
		CSVPrinter::CSVPrinter (const Config& config) :
			headers (config.get ("headers", 0)),
			quote (config.get ("quote", "")),
			split (config.get ("split", ","))
		{
		}

		void	CSVPrinter::print (OStream& stream, const Table& table)
		{
			const Table::Columns&	columns (table.getColumns ());
			string					output;
			Variant*				value;
			Int32u					width (table.getWidth ());
			FormatWriter			writer (stream);

			if (this->headers)
			{
				for (Int32u i = 0; i < width; ++i)
				{
					if (i > 0)
						writer.write (this->split);

					writer
						.write (this->quote)
						.write (columns[i].getKey ())
						.write (this->quote);
				}

				writer.write ("\n");
			}

			for (auto row = table.begin (); row != table.end (); ++row)
			{
				value = *row;

				for (Int32u i = 0; i < width; ++i)
				{
					if (i > 0)
						writer.write (this->split);

					if (value->toString (&output))
					{
						writer
							.write (this->quote)
							.write (output)
							.write (this->quote);
					}

					++value;
				}

				writer.write ("\n");
			}
		}
	}
}

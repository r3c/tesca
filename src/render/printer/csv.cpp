
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
			StringWriter	writer (stream);

			if (this->headers)
			{
				auto	columns = table.getColumns ();

				for (Int32u i = 0; i < columns.size (); ++i)
				{
					if (i > 0)
						writer.writeString (this->split);

					writer.writeString (this->quote);
					writer.writeString (columns[i]->getIdentifier ());
					writer.writeString (this->quote);
				}

				writer.writeString ("\n");
			}

			width = table.getWidth ();

			for (auto row = table.begin (); row != table.end (); ++row)
			{
				auto	slot = row->second;

				for (Int32u i = 0; i < width; ++i)
				{
					if (i > 0)
						writer.writeString (this->split);

					if ((*slot)->current ().toString (&value))
					{
						writer.writeString (this->quote);
						writer.writeString (value);
						writer.writeString (this->quote);
					}

					++slot;
				}

				writer.writeString ("\n");
			}
		}
	}
}

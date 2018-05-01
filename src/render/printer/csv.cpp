
#include "csv.hpp"

#include <string>

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Tesca::Arithmetic;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Render
	{
		CSVPrinter::CSVPrinter (Config const& config) :
			headers (config.get ("headers", 0)),
			quote (config.get ("quote", "\"")),
			split (config.get ("split", ","))
		{
		}

		void CSVPrinter::print (OStream& stream, Table const& table) const
		{
			Table::Columns const& columns (table.getColumns ());
			string output;
			Variant* value;
			Int32u width (table.getWidth ());
			FormatWriter writer (stream);

			if (this->headers)
			{
				for (Int32u i = 0; i < width; ++i)
				{
					if (i > 0)
						writer.write (this->split);

					this->write (writer, columns[i].getKey ());
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
						this->write (writer, output);

					++value;
				}

				writer.write ("\n");
			}
		}

		void CSVPrinter::write (FormatWriter& writer, const string& value) const
		{
			bool escape;

			escape = value.find (this->quote) != string::npos || value.find (this->split) != string::npos;

			if (escape)
				writer.write (this->quote);

			writer.write (value);

			if (escape)
				writer.write (this->quote);
		}
	}
}

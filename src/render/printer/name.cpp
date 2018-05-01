
#include "name.hpp"

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
		NamePrinter::NamePrinter (Config const&)
		{
		}

		void NamePrinter::print (OStream& stream, Table const& table) const
		{
			Table::Columns const& columns (table.getColumns ());
			string output;
			Variant* value;
			Int32u width (table.getWidth ());
			FormatWriter writer (stream);

			for (auto row = table.begin (); row != table.end (); ++row)
			{
				value = *row;

				for (Int32u i = 0; i < width; ++i)
				{
					if (i > 0)
						writer.write (", ");

					if (!value->toString (&output))
						output = "<void>";

					writer
						.write (columns[i].getKey ())
						.write (" = ")
						.write (output);

					++value;
				}

				writer.write ("\n");
			}
		}
	}
}

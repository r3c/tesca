
#include "name.hpp"

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
		NamePrinter::NamePrinter (const Config&)
		{
		}

		NamePrinter::~NamePrinter ()
		{
		}

		void	NamePrinter::print (OStream& stream, const Table& table)
		{
			string			value;
			FormatWriter	writer (stream);

			for (auto iterator = table.begin (); iterator != table.end (); ++iterator)
			{
				const Arithmetic::Slot* const*	slots = iterator->second;

				for (Int32u i = 0; i < table.getWidth (); ++i)
				{
					const Arithmetic::Slot*	slot = slots[i];

					if (i > 0)
						writer.write (", ");

					auto id = table.getColumns ()[i]->getIdentifier ();

					if (!slot->current ().toString (&value))
						value = "<void>";

					writer
						.write (id)
						.write (" = ")
						.write (value);
				}

				writer.write ("\n");
			}
		}
	}
}

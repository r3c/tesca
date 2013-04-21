
#include "name.hpp"

#include <string>

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Tesca::Arithmetic;

namespace	Tesca
{
	namespace	Render
	{
		NamePrinter::NamePrinter ()
		{
		}

		NamePrinter::~NamePrinter ()
		{
		}

		void	NamePrinter::print (OStream& stream, const Table& table)
		{
			string	value;

			for (auto iterator = table.begin (); iterator != table.end (); ++iterator)
			{
				const Arithmetic::Slot* const*	slots = iterator->second;

				for (Int32u i = 0; i < table.getWidth (); ++i)
				{
					const Arithmetic::Slot&	slot = *slots[i];

					if (i > 0)
						stream.write (", ", 2); // FIXME

					auto id = table.getColumns ()[i]->getIdentifier ();

					if (!slot.current ().toString (&value))
						value = "<void>";

					stream.write (id.c_str (), id.length ());
					stream.write (" = ", 3); // FIXME
					stream.write (value.c_str (), value.length ());
				}

				stream.write ("\n", 1); // FIXME
			}
		}
	}
}

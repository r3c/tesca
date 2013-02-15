
#include <iostream>
#include <vector>
#include "arithmetic/accessor/binary.hpp"
#include "arithmetic/accessor/constant.hpp"
#include "arithmetic/accessor/field.hpp"
#include "arithmetic/column/group.hpp"
#include "arithmetic/column/value.hpp"
#include "arithmetic/slot/average.hpp"
#include "arithmetic/slot/last.hpp"
#include "arithmetic/slot/sum.hpp"
#include "arithmetic/table.hpp"
#include "expression/formula.hpp"
#include "stream/reader/map.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca;

void	debug_print (const Table& table)
{
	for (auto iterator = table.begin (); iterator != table.end (); ++iterator)
	{
		const Slot* const*	slots = iterator->second;

		for (Int32u i = 0; i < table.getWidth (); ++i)
		{
			const Slot&	slot = *slots[i];

			if (i > 0)
				std::cout << ", ";

			std::cout << "[" << table.getColumns ()[i]->getIdentifier () << "] = " << slot.current ();
		}

		std::cout << std::endl;
	}

	std::cout << "---" << std::endl;
}

int	main (int argc, char* argv[])
{
	vector<const Column*>	columns;
	Formula					formula;

	if (argc > 1)
	{
		if (!formula.parse (argv[1]))
		{
			std::cout << "error: " << formula.getError () << std::endl;

			return 1;
		}

		columns = formula.getColumns ();
	}
	else
	{
		columns = vector<const Column*> ();
		columns.push_back (new ValueColumn ("a", new FieldAccessor ("0")));
		columns.push_back (new GroupColumn<AverageSlot> ("b", new FieldAccessor ("1")));
		columns.push_back (new GroupColumn<SumSlot> ("c", new FieldAccessor ("1")));
		columns.push_back (new ValueColumn ("d", new ConstantAccessor (Variant (42))));
	}

	MapReader	reader;
	Table		table (columns);

	reader.push ();
	reader.set ("0", Variant ("A"));
	reader.set ("1", Variant (1));
	reader.push ();
	reader.set ("0", Variant ("A"));
	reader.set ("1", Variant ("2"));
	reader.push ();
	reader.set ("0", Variant (8));
	reader.set ("1", Variant (3));
	reader.push ();
	reader.set ("0", Variant ("8"));
	reader.set ("1", Variant (4));

	while (reader.next ())
	{
		table.push (reader.current ());

		debug_print (table);
	}
}

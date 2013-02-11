
#include <iostream>
#include <map>
#include <vector>
#include "arithmetic/column/group.hpp"
#include "arithmetic/column/value.hpp"
#include "arithmetic/reader/binary.hpp"
#include "arithmetic/reader/constant.hpp"
#include "arithmetic/reader/field.hpp"
#include "arithmetic/row.hpp"
#include "arithmetic/table.hpp"
#include "arithmetic/slot/average.hpp"
#include "arithmetic/slot/last.hpp"
#include "arithmetic/slot/sum.hpp"
#include "expression/formula.hpp"

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
	Row						row;

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
		columns.push_back (new ValueColumn ("a", new FieldReader ("0")));
		columns.push_back (new GroupColumn<AverageSlot> ("b", new FieldReader ("1")));
		columns.push_back (new GroupColumn<SumSlot> ("c", new FieldReader ("1")));
		columns.push_back (new ValueColumn ("d", new ConstantReader (Variant (42))));
	}

	Table	table (columns);

	row.clear ();
	row.push ("0", Variant ("A"));
	row.push ("1", Variant (1));

	table.push (row);

	debug_print (table);

	row.clear ();
	row.push ("0", Variant ("A"));
	row.push ("1", Variant ("2"));

	table.push (row);

	debug_print (table);

	row.clear ();
	row.push ("0", Variant (8));
	row.push ("1", Variant (3));

	table.push (row);

	debug_print (table);

	row.clear ();
	row.push ("0", Variant ("8"));
	row.push ("1", Variant (4));

	table.push (row);

	debug_print (table);
}

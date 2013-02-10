
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
	vector<Column*>				columns;
	Formula						formula;
	Row*						row;
	map<string, const Variant*>	values;

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
		columns = vector<Column*> ();
		columns.push_back (new ValueColumn ("a", new FieldReader ("0")));
		columns.push_back (new GroupColumn<AverageSlot> ("b", new FieldReader ("1")));
		columns.push_back (new GroupColumn<SumSlot> ("c", new FieldReader ("1")));
		columns.push_back (new ValueColumn ("d", new ConstantReader (Variant (42))));
	}

	Table	table (columns);

	values.clear ();
	values["0"] = new Variant ("A");
	values["1"] = new Variant (1);

	row = new Row (values);

	table.push (*row);

	delete values["0"];
	delete values["1"];

	debug_print (table);

	values.clear ();
	values["0"] = new Variant ("A");
	values["1"] = new Variant ("2");

	row = new Row (values);

	table.push (*row);

	delete values["0"];
	delete values["1"];

	debug_print (table);

	values.clear ();
	values["0"] = new Variant (8);
	values["1"] = new Variant (3);

	row = new Row (values);

	table.push (*row);

	delete values["0"];
	delete values["1"];

	debug_print (table);

	values.clear ();
	values["0"] = new Variant ("8");
	values["1"] = new Variant (4);

	row = new Row (values);

	table.push (*row);

	delete values["0"];
	delete values["1"];

	debug_print (table);
}

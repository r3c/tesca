
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
	const char*	expression;
	Formula		formula;

	if (argc < 2)
		expression = "a = $aaa, b:sum = $bbb, c:avg = $bbb";
	else
		expression = argv[1];

	if (!formula.parse (expression))
	{
		std::cout << "error: " << formula.getError () << std::endl;

		return 1;
	}

	MapReader	reader (&formula.getFields ());
	Table		table (&formula.getColumns ());

	reader.push ();
	reader.assign ("aaa", Variant ("A"));
	reader.assign ("bbb", Variant (1));
	reader.push ();
	reader.assign ("aaa", Variant ("A"));
	reader.assign ("bbb", Variant ("2"));
	reader.push ();
	reader.assign ("aaa", Variant (8));
	reader.assign ("bbb", Variant (3));
	reader.push ();
	reader.assign ("aaa", Variant ("8"));
	reader.assign ("bbb", Variant (4));

	while (reader.next ())
	{
		table.push (reader.current ());

		debug_print (table);
	}
}

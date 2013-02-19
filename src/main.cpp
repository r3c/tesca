
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
#include "stream/reader/line/csv.hpp"
#include "stream/reader/line/regex.hpp"
#include "stream/reader/map.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca;

ostream&	operator << (ostream& stream, const Variant& value)
{
	bool	asBoolean;
	Float64	asNumber;
	string	asString;

	switch (value.getType ())
	{
		case Tesca::Variant::BOOLEAN:
			if (value.toBoolean (&asBoolean))
				stream << (asBoolean ? "true" : "false");
			else
				stream << "!";

			break;

		case Tesca::Variant::NUMBER:
			if (value.toNumber (&asNumber))
				stream << asNumber;
			else
				stream << "!";

			break;

		case Tesca::Variant::STRING:
			if (value.toString (&asString))
				stream << asString;
			else
				stream << "!";

			break;

		case Tesca::Variant::NONE:
			stream << "void";

			break;

		default:
			stream << "?";

			break;
	}

	return stream;
}

void	debug_print (const Table& table)
{
	for (auto iterator = table.begin (); iterator != table.end (); ++iterator)
	{
		const Slot* const*	slots = iterator->second;

		for (Int32u i = 0; i < table.getWidth (); ++i)
		{
			const Slot&	slot = *slots[i];

			if (i > 0)
				cout << ", ";

			cout << "[" << table.getColumns ()[i]->getIdentifier () << "] = " << slot.current ();
		}

		cout << endl;
	}

	cout << "---" << endl;
}

int	main (int argc, char* argv[])
{
	const char*	expression;
	Formula		formula;
	Reader*		reader;

	if (argc > 3)
	{
		if (!formula.parse (argv[1]))
		{
			cout << "error: " << formula.getError () << endl;

			return 1;
		}

		reader = new RegexLineReader (new Pipe::FileIStream (argv[2]), &formula.getFields (), argv[3]);
	}
	else if (argc > 2)
	{
		if (!formula.parse (argv[1]))
		{
			cout << "error: " << formula.getError () << endl;

			return 1;
		}

		reader = new CSVLineReader (new Pipe::FileIStream (argv[2]), &formula.getFields (), false, ',');
	}
	else
	{
		if (argc > 1)
			expression = argv[1];
		else
			expression = "a = $aaa, b:sum = $bbb, c:avg = $bbb";

		if (!formula.parse (expression))
		{
			cout << "error: " << formula.getError () << endl;

			return 1;
		}

		MapReader*	m = new MapReader (&formula.getFields ());

		m->push ();
		m->assign ("aaa", Variant ("A"));
		m->assign ("bbb", Variant (1));
		m->push ();
		m->assign ("aaa", Variant ("A"));
		m->assign ("bbb", Variant ("2"));
		m->push ();
		m->assign ("aaa", Variant (8));
		m->assign ("bbb", Variant (3));
		m->push ();
		m->assign ("aaa", Variant ("8"));
		m->assign ("bbb", Variant (4));

		reader = m;
	}

	Table	table (&formula.getColumns ());

	while (reader->next ())
		table.push (reader->current ());

	debug_print (table);

	delete reader;
}

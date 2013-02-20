
#include <iostream>
#include <vector>
#include "arithmetic/table.hpp"
#include "expression/formula.hpp"
#include "stream/format.hpp"

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
}

bool	debug_read (Table& table, const Format& format, Pipe::IStream* stream, const Reader::Fields* fields, const char* expression)
{
	Reader*	reader;

	reader = format.create (stream, fields, expression);

	if (!reader)
	{
		cerr << "error: cannot use format \"" << expression << "\"" << endl;

		return false;
	}

	while (reader->next ())
		table.push (reader->current ());

	delete reader;

	return true;
}

int	main (int argc, char* argv[])
{
	Format	format;
	Formula	formula;

	if (argc < 3)
	{
		cout << "usage: " << argv[0] << " <formula> <format> [<file> [<file>...]]" << endl;

		return 0;
	}

	if (!formula.parse (argv[1]))
	{
		cerr << "error: " << formula.getError () << endl;

		return 1;
	}

	Table	table (&formula.getColumns ());

	if (argc > 3)
	{
		for (int i = 3; i < argc; ++i)
		{
			Pipe::FileIStream	stream (argv[i]);

			if (stream)
				debug_read (table, format, &stream, &formula.getFields (), argv[2]);
			else
				cerr << "error: cannot open file \"" << argv[i] << "\" for reading" << endl;
		}
	}
	else
	{
		Pipe::StandardIStream	stream (&cin);

		if (stream)
			debug_read (table, format, &stream, &formula.getFields (), argv[2]);
		else
			cerr << "error: cannot read from standard output" << endl;
	}

	debug_print (table);
}

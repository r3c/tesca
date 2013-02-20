
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

int	main (int argc, char* argv[])
{
	Format			format;
	Formula			formula;
	Reader*			reader;
	Pipe::IStream*	stream;

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
			stream = new Pipe::FileIStream (argv[i]);

			if (*stream)
			{
				reader = format.create (stream, &formula.getFields (), argv[2]);

				if (reader)
				{
					while (reader->next ())
						table.push (reader->current ());

					delete reader;
				}
				else
					cerr << "error: cannot use format \"" << argv[2] << "\"" << endl;

				delete stream;
			}
			else
				cerr << "error: cannot open file \"" << argv[i] << "\" for reading" << endl;
		}
	}
	else
	{
		stream = new Pipe::StandardIStream (&cin);
		reader = format.create (stream, &formula.getFields (), argv[2]);

		if (reader)
		{
			while (reader->next ())
				table.push (reader->current ());

			delete reader;
		}
		else
			cerr << "error: cannot use format \"" << argv[2] << "\"" << endl;

		delete stream;
	}

	debug_print (table);
}


#include <iostream>
#include <vector>
#include "arithmetic/lookup.hpp"
#include "arithmetic/table.hpp"
#include "expression/formula.hpp"
#include "expression/select.hpp"
#include "stream/format.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca;

#include "stream/reader/line.hpp"
#include "stream/row/array.hpp"

class	MyLineReader : public LineReader
{
	public:
		MyLineReader (Pipe::IStream* stream) :
			LineReader (stream),
			count (0),
			row (0)
		{
		}

		Int32u	getCount () const
		{
			return this->count;
		}

		virtual const Row&	current () const
		{
			return this->row;
		}

	protected:
		virtual void	parse (const char*, Int32u)
		{
			++this->count;
		}

	private:
		Int32u		count;
		ArrayRow	row;
};

ostream&	operator << (ostream& stream, const Variant& value)
{
	string	buffer;

	if (value.toString (&buffer))
		stream << buffer;
	else
		stream << "!";

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

bool	debug_read (Table& table, const Format& format, const Lookup& lookup, Pipe::IStream* stream)
{
	Reader*	reader;

	reader = format.create (stream, lookup);

	if (!reader)
		return false;

	while (reader->next ())
		table.push (reader->current ());

	delete reader;

	return true;
}

int	main (int argc, char* argv[])
{
	Format				format;
	const char*			formatString;
	Expression::Formula	formula;
	const char*			formulaString;
	int					index;
	Lookup				lookup;
//	const char*			outputString;
	Expression::Select	select;
	const char*			selectString;
	Pipe::FileIStream*	stream;
	Table				table;

	formatString = "csv";
	formulaString = "nb_lines:count";
	selectString = "1";

	for (index = 1; index < argc && argv[index][0] == '-'; ++index)
	{
		switch (argv[index][1])
		{
			case 'f':
				if (++index >= argc)
				{
					cerr << "error: missing formula expression argument" << endl;

					return 1;
				}

				formulaString = argv[index];

				break;

			case 'h':
				cout << "usage: " << argv[0] << " [-i <format>] [-f <formula>] [<file> [<file>...]]" << endl;
				cout << "  -f: result formula, e.g. 'name = $0, duration = $1:sum'" << endl;
				cout << "  -i: input format, e.g. 'csv'" << endl;
//				cout << "  -o: output format, e.g. 'FIXME'" << endl;
				cout << "  -s: selection filter, e.g. 'ge(len($0), 4)'" << endl;

				return 0;

			case 'i':
				if (++index >= argc)
				{
					cerr << "error: missing input format argument" << endl;

					return 1;
				}

				formatString = argv[index];

				break;

			case 's':
				if (++index >= argc)
				{
					cerr << "error: missing select filter argument" << endl;

					return 1;
				}

				selectString = argv[index];

				break;

			default:
				cerr << "error: unknown option '" << argv[index][1] << "'" << endl;

				return 1;
		}
	}

	if (!format.parse (formatString))
	{
		cerr << "error: invalid input format" << endl;

		return 1;
	}

	if (!formula.parse (lookup, formulaString))
	{
		cerr << "error: invalid formula expression (" << formula.getMessage () << ")" << endl;

		return 1;
	}

	if (!select.parse (lookup, selectString))
	{
		cerr << "error: invalid select expression (" << select.getMessage () << ")" << endl;

		return 1;
	}

	table.reset (select.getAccessor (), formula.getColumns ());

	do
	{
		if (index < argc)
			stream = new Pipe::FileIStream (argv[index]);
		else
			stream = new Pipe::FileIStream (stdin);

		if (*stream)
			debug_read (table, format, lookup, stream);
		else if (index < argc)
			cerr << "error: cannot open file '" << argv[index] << "' for reading" << endl;
		else
			cerr << "error: cannot open standard input for reading" << endl;

		delete stream;
	}
	while (++index < argc);

	debug_print (table);
}

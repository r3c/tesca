
#include <iostream>
#include <vector>
#include "arithmetic/table.hpp"
#include "expression/formula.hpp"
#include "expression/select.hpp"
#include "provision/lookup.hpp"
#include "provision/format.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Tesca;

ostream&	operator << (ostream& stream, const Provision::Variant& value)
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

int	debug_run (const char* formatString, const char* condition, const char* aggregation, char* paths[], int length)
{
	Provision::Format	format;
	Expression::Formula	formula;
	int					index;
	Provision::Lookup	lookup;
	Provision::Reader*	reader;
	Expression::Select	select;
	FileIStream*		stream;
	Table				table;
/*
	format.getError ().bind ([] (const string& message)
	{
		cerr << "error: invalid input format (" << message << ")" << endl;
	});
*/
	if (!format.parse (formatString))
	{
		cerr << "error: invalid input format" << endl;

		return 1;
	}

	formula.getError ().bind ([] (const string& message)
	{
		cerr << "error: invalid aggregation expression (" << message << ")" << endl;
	});

	if (!formula.parse (lookup, aggregation))
		return 1;

	select.getError ().bind ([] (const string& message)
	{
		cerr << "error: invalid condition expression (" << message << ")" << endl;
	});

	if (!select.parse (lookup, condition))
		return 1;

	table.reset (select.getCondition (), formula.getColumns ());

	for (index = 0; index < length || index == 0; ++index)
	{
		if (index < length)
			stream = new FileIStream (paths[index]);
		else
			stream = new FileIStream (stdin);

		if (*stream)
		{
			reader = format.create (stream, lookup);

			if (reader)
			{
				reader->getError ().bind ([] (const string& error)
				{
					cerr << "warning: reader error (" << error << ")" << endl;
				});

				while (reader->next ())
					table.push (reader->current ());

				delete reader;
			}
			else
				cerr << "error: cannot create reader" << endl;
		}
		else if (index < length)
			cerr << "error: cannot open file '" << paths[index] << "' for reading" << endl;
		else
			cerr << "error: cannot open standard input for reading" << endl;

		delete stream;
	}

	debug_print (table);

	return 0;
}

int	main (int argc, char* argv[])
{
	const char*	aggregation;
	const char*	condition;
	const char*	format;
	int			index;
//	const char*	output;

	aggregation = "nb_lines:count";
	condition = "1";
	format = "csv";

	for (index = 1; index < argc && argv[index][0] == '-'; ++index)
	{
		switch (argv[index][1])
		{
			case 'a':
				if (++index >= argc)
				{
					cerr << "error: missing aggregation argument" << endl;

					return 1;
				}

				aggregation = argv[index];

				break;

			case 'c':
				if (++index >= argc)
				{
					cerr << "error: missing condition argument" << endl;

					return 1;
				}

				condition = argv[index];

				break;

			case 'h':
				cout << "usage: " << argv[0] << " [-i <format>] [-c <condition>] [-a <aggregation>] [<file> [<file>...]]" << endl;
				cout << "  -a: aggregation expression, e.g. 'name = $0, duration = $1:sum'" << endl;
				cout << "  -c: filter condition, e.g. 'ge(len($0), 4)'" << endl;
				cout << "  -i: input format, e.g. 'csv'" << endl;
//				cout << "  -o: output format, e.g. 'FIXME'" << endl;

				return 0;

			case 'i':
				if (++index >= argc)
				{
					cerr << "error: missing input format argument" << endl;

					return 1;
				}

				format = argv[index];

				break;

			default:
				cerr << "error: unknown option '" << argv[index][1] << "'" << endl;

				return 1;
		}
	}

	return debug_run (format, condition, aggregation, argv + index, argc - index);
}

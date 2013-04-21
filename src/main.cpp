
#include <iostream>
#include "arithmetic/table.hpp"
#include "expression/calculator.hpp"
#include "expression/filter.hpp"
#include "provision/input.hpp"
#include "provision/lookup.hpp"
#include "render/output.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Tesca;

int	execute (const Provision::Input& input, const Provision::Lookup& lookup, const Expression::Filter& filter, Expression::Calculator& calculator, const Render::Output& output, char* sources[], int length)
{
	int					index;
	Render::Printer*	printer;
	Provision::Reader*	reader;
	FileIStream*		source;
	Arithmetic::Table	table;
	FileOStream			target (stdout);

	printer = output.create ();

	if (!printer)
	{
		cerr << "error: cannot create printer" << endl;

		return 1;
	}

	table.reset (filter.getCondition (), calculator.getColumns ());

	for (index = 0; index < length || index == 0; ++index)
	{
		if (index < length)
			source = new FileIStream (sources[index]);
		else
			source = new FileIStream (stdin);

		if (*source)
		{
			reader = input.create (source, lookup);

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
			cerr << "error: cannot open file '" << sources[index] << "' for reading" << endl;
		else
			cerr << "error: cannot open standard input for reading" << endl;

		delete source;
	}

	printer->print (target, table);

	delete printer;

	return 0;
}

int	main (int argc, char* argv[])
{
	Expression::Calculator	calculator;
	const char*				calculatorExpression;
	Expression::Filter		filter;
	const char*				filterCondition;
	int						index;
	Provision::Input		input;
	const char*				inputFormat;
	Provision::Lookup		lookup;
	Render::Output			output;
	const char*				outputFormat;

	calculator.getError ().bind ([] (const string& message)
	{
		cerr << "error: invalid calculator expression (" << message << ")" << endl;
	});

	filter.getError ().bind ([] (const string& message)
	{
		cerr << "error: invalid filter condition (" << message << ")" << endl;
	});

	input.getError ().bind ([] (const string& message)
	{
		cerr << "error: invalid input format (" << message << ")" << endl;
	});

	output.getError ().bind ([] (const string& message)
	{
		cerr << "error: invalid output format (" << message << ")" << endl;
	});

	calculatorExpression = "nb_lines:count";
	filterCondition = "1";
	inputFormat = "csv";
	outputFormat = "name";

	for (index = 1; index < argc && argv[index][0] == '-'; ++index)
	{
		for (const char* argument = argv[index] + 1; *argument != '\0'; ++argument)
		{
			switch (*argument)
			{
				case 'c':
					if (++index >= argc)
					{
						cerr << "error: missing filter condition" << endl;

						return 1;
					}

					filterCondition = argv[index];

					break;

				case 'e':
					if (++index >= argc)
					{
						cerr << "error: missing calculator expression" << endl;

						return 1;
					}

					calculatorExpression = argv[index];

					break;

				case 'h':
					cout << "usage: " << argv[0] << " [-i <format>] [-o <printer>] [-c <condition>] [-e <expression>] [<file> [<file>...]]" << endl;
					cout << "  -c: filter condition, e.g. 'ge(len($0), 4)'" << endl;
					cout << "  -e: calculator expression, e.g. 'name = $0, duration = $1:sum'" << endl;
					cout << "  -i: input format, e.g. 'csv'" << endl;
					cout << "  -o: output format, e.g. 'csv'" << endl;

					return 0;

				case 'i':
					if (++index >= argc)
					{
						cerr << "error: missing input format" << endl;

						return 1;
					}

					inputFormat = argv[index];

					break;

				case 'o':
					if (++index >= argc)
					{
						cerr << "error: missing output format" << endl;

						return 1;
					}

					outputFormat = argv[index];

					break;

				default:
					cerr << "error: unknown option '" << *argument << "'" << endl;

					return 1;
			}
		}
	}

	if (!calculator.parse (lookup, calculatorExpression) ||
	    !filter.parse (lookup, filterCondition) ||
		!input.parse (inputFormat) ||
		!output.parse (outputFormat))
		return 1;

	return execute (input, lookup, filter, calculator, output, argv + index, argc - index);
}


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
	FileOStream			errorStream (stderr);
	StringWriter		errorWriter (errorStream);
	Render::Printer*	printer;
	Provision::Reader*	reader;
	FileIStream*		source;
	Arithmetic::Table	table;
	FileOStream			target (stdout);

	printer = output.create ();

	if (!printer)
	{
		errorWriter.writeString ("error: cannot create printer\n");

		return 1;
	}

	table.reset (filter.getCondition (), calculator.getColumns ());

	for (int index = 0; index < length || index == 0; ++index)
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
				reader->getError ().bind ([&] (const string& error)
				{
					errorWriter.writeString ("warning: reader error(");
					errorWriter.writeString (error);
					errorWriter.writeString (")\n");
				});

				while (reader->next ())
					table.push (reader->current ());

				delete reader;
			}
			else
				errorWriter.writeString ("error: cannot create reader\n");
		}
		else if (index < length)
		{
			errorWriter.writeString ("error: cannot open file '");
			errorWriter.writeString (sources[index]);
			errorWriter.writeString ("' for reading\n");
		}
		else
			errorWriter.writeString ("error: cannot open standard input for reading");

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
	FileOStream				errorStream (stderr);
	StringWriter			errorWriter (errorStream);
	Expression::Filter		filter;
	const char*				filterCondition;
	Provision::Input		input;
	const char*				inputFormat;
	Provision::Lookup		lookup;
	Render::Output			output;
	const char*				outputFormat;
	int						start;
	FileOStream				stdStream (stdout);
	StringWriter			stdWriter (stdStream);

	calculator.getError ().bind ([&] (const string& message)
	{
		errorWriter.writeString ("error: invalid calculator expression (");
		errorWriter.writeString (message);
		errorWriter.writeString (")\n");
	});

	filter.getError ().bind ([&] (const string& message)
	{
		errorWriter.writeString ("error: invalid filter condition (");
		errorWriter.writeString (message);
		errorWriter.writeString (")\n");
	});

	input.getError ().bind ([&] (const string& message)
	{
		errorWriter.writeString ("error: invalid input format (");
		errorWriter.writeString (message);
		errorWriter.writeString (")\n");
	});

	output.getError ().bind ([&] (const string& message)
	{
		errorWriter.writeString ("error: invalid output format (");
		errorWriter.writeString (message);
		errorWriter.writeString (")\n");
	});

	calculatorExpression = "nb_lines:count";
	filterCondition = "true";
	inputFormat = "csv";
	outputFormat = "name";

	for (start = 1; start < argc && argv[start][0] == '-'; ++start)
	{
		for (const char* argument = argv[start] + 1; *argument != '\0'; ++argument)
		{
			switch (*argument)
			{
				case 'c':
					if (++start >= argc)
					{
						errorWriter.writeString ("error: missing filter condition\n");

						return 1;
					}

					filterCondition = argv[start];

					break;

				case 'e':
					if (++start >= argc)
					{
						errorWriter.writeString ("error: missing calculator expression\n");

						return 1;
					}

					calculatorExpression = argv[start];

					break;

				case 'h':
					stdWriter.writeString ("usage: ");
					stdWriter.writeString (argv[0]);
					stdWriter.writeString (" [-i <format>] [-o <printer>] [-c <condition>] [-e <expression>] [<file> [<file>...]]\n");
					stdWriter.writeString ("  -c: filter condition, e.g. 'ge(len($0), 4)'\n");
					stdWriter.writeString ("  -e: calculator expression, e.g. 'name = $0, duration = $1:sum'\n");
					stdWriter.writeString ("  -i: input format, e.g. 'csv'\n");
					stdWriter.writeString ("  -o: output format, e.g. 'csv'\n");

					return 0;

				case 'i':
					if (++start >= argc)
					{
						errorWriter.writeString ("error: missing input format\n");

						return 1;
					}

					inputFormat = argv[start];

					break;

				case 'o':
					if (++start >= argc)
					{
						errorWriter.writeString ("error: missing output format\n");

						return 1;
					}

					outputFormat = argv[start];

					break;

				default:
					errorWriter.writeString ("error: unknown option '");
//					errorWriter.writeString (*argument);
					errorWriter.writeString ("'");

					return 1;
			}
		}
	}

	if (!calculator.parse (lookup, calculatorExpression) ||
	    !filter.parse (lookup, filterCondition) ||
		!input.parse (inputFormat) ||
		!output.parse (outputFormat))
		return 1;

	return execute (input, lookup, filter, calculator, output, argv + start, argc - start);
}

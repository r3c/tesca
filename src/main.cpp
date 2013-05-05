
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
	Render::Printer*	printer;
	Provision::Reader*	reader;
	FileIStream*		source;
	Arithmetic::Table	table;
	FileOStream			target (stdout);
	FormatWriter		writer (err);

	printer = output.create ();

	if (!printer)
	{
		writer.write ("error: cannot create printer\n");

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
					writer
						.write ("warning: reader error(")
						.write (error)
						.write(")\n");
				});

				while (reader->next ())
					table.push (reader->current ());

				delete reader;
			}
			else
				writer.write ("error: cannot create reader\n");
		}
		else if (index < length)
		{
			writer
				.write ("error: cannot open file '")
				.write (sources[index])
				.write ("' for reading\n");
		}
		else
			writer.write ("error: cannot open standard input for reading");

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
	FormatWriter			console (out);
	Expression::Filter		filter;
	const char*				filterCondition;
	Provision::Input		input;
	const char*				inputFormat;
	Provision::Lookup		lookup;
	Render::Output			output;
	const char*				outputFormat;
	int						start;
	FormatWriter			writer (err);

	calculator.getError ().bind ([&] (const string& message)
	{
		writer
			.write ("error: invalid calculator expression (")
			.write (message)
			.write (")\n");
	});

	filter.getError ().bind ([&] (const string& message)
	{
		writer
			.write ("error: invalid filter condition (")
			.write (message)
			.write (")\n");
	});

	input.getError ().bind ([&] (const string& message)
	{
		writer
			.write ("error: invalid input format (")
			.write (message)
			.write (")\n");
	});

	output.getError ().bind ([&] (const string& message)
	{
		writer
			.write ("error: invalid output format (")
			.write (message)
			.write (")\n");
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
						writer.write ("error: missing filter condition\n");

						return 1;
					}

					filterCondition = argv[start];

					break;

				case 'e':
					if (++start >= argc)
					{
						writer.write ("error: missing calculator expression\n");

						return 1;
					}

					calculatorExpression = argv[start];

					break;

				case 'h':
					console
						.write ("usage: ")
						.write (argv[0])
						.write (" [-i <format>] [-o <printer>] [-c <condition>] [-e <expression>] [<file> [<file>...]]\n")
						.write ("  -c: filter condition, e.g. 'len($0) >= 3'\n")
						.write ("  -e: calculator expression, e.g. 'name = $0, duration = $1:sum'\n")
						.write ("  -i: input format, e.g. 'csv'\n")
						.write ("  -o: output format, e.g. 'csv'\n");

					return 0;

				case 'i':
					if (++start >= argc)
					{
						writer.write ("error: missing input format\n");

						return 1;
					}

					inputFormat = argv[start];

					break;

				case 'o':
					if (++start >= argc)
					{
						writer.write ("error: missing output format\n");

						return 1;
					}

					outputFormat = argv[start];

					break;

				default:
					writer
						.write ("error: unknown option '")
//						.write (*argument) // FIXME
						.write ("'");

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

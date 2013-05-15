
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

void	initialize (Arithmetic::Table& table, const Expression::Filter& filter, Expression::Calculator& calculator)
{
	table.reset (filter.getCondition (), calculator.getColumns (), calculator.getSlots ());
}

void	loading (FormatWriter& writer, const char* caption, const Provision::Reader::Progress& progress)
{
	static const Int32u	captionWidth = 30;
	static const Int32u	meterWidth = 25;

	Int32u	i;
	Int32u	u;

	writer.write ('\r');

	for (i = 0; i < captionWidth && *caption != '\0'; ++i)
		writer.write (*caption++);

	for (; i < captionWidth; ++i)
		writer.write (' ');

	writer
		.write (" [");

	u = progress.read * meterWidth / progress.size;

	for (i = 0; i < u; ++i)
		writer.write ('#');

	for (i = u; i < meterWidth; ++i)
		writer.write ('-');

	writer
		.write ("] ")
		.write (progress.read * 100 / progress.size)
		.write ('%')
		.flush ();
}

void	process (Arithmetic::Table& table, const Provision::Input& input, const Provision::Lookup& lookup, bool progress, char* sources[], int length)
{
	const char*			caption;
	Provision::Reader*	reader;
	FileIStream			source;
	Int8u				status;
	FormatWriter		writer (err);

	status = progress ? 1 : 0;

	for (int index = 0; index < length || index == 0; ++index)
	{
		if (index < length)
		{
			source.open (sources[index]);

			caption = sources[index];
		}
		else
		{
			source.open (stdin);

			caption = "<standard input>";
		}

		if (source)
		{
			reader = input.create (&source, lookup);

			if (reader)
			{
				reader->onError ().bind ([&] (const string& error)
				{
					if (status > 1)
						writer.write ("\n");

					writer
						.write ("warning: reader error(")
						.write (error)
						.write(")\n");
				});

				
				reader->onRead ().bind ([&] (const Provision::Reader::Progress& progress)
				{
					if (status > 0 && progress.size > 0)
					{
						loading (writer, caption, progress);

						status = 2;
					}
				});

				while (reader->next ())
					table.push (reader->current ());

				if (status > 1)
				{
					writer
						.write ("\n")
						.flush ();
				}

				delete reader;
			}
			else
				writer.write ("error: cannot create reader\n");
		}
		else
		{
			writer
				.write ("error: cannot open '")
				.write (caption)
				.write ("' for reading\n");
		}
	}
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
	Render::Printer*		printer;
	bool					progress;
	int						start;
	Arithmetic::Table		table;
	FormatWriter			writer (err);

	calculator.onError ().bind ([&] (const string& message)
	{
		writer
			.write ("error: invalid calculator expression (")
			.write (message)
			.write (")\n");
	});

	filter.onError ().bind ([&] (const string& message)
	{
		writer
			.write ("error: invalid filter condition (")
			.write (message)
			.write (")\n");
	});

	input.onError ().bind ([&] (const string& message)
	{
		writer
			.write ("error: invalid input format (")
			.write (message)
			.write (")\n");
	});

	output.onError ().bind ([&] (const string& message)
	{
		writer
			.write ("error: invalid output format (")
			.write (message)
			.write (")\n");
	});

	calculatorExpression = "count():nb_lines";
	filterCondition = "true";
	inputFormat = "csv";
	outputFormat = "pretty";
	progress = false;

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
						.write ("  -c: filter condition, e.g. 'len(#0) >= 3'\n")
						.write ("  -e: calculator expression, e.g. '#0: name, sum(#1): duration'\n")
						.write ("  -i: input stream format, e.g. 'csv'\n")
						.write ("  -o: output stream format, e.g. 'csv'\n")
						.write ("  -p: display progress bar\n");

					return 0;

				case 'i':
					if (++start >= argc)
					{
						writer.write ("error: missing input stream format\n");

						return 1;
					}

					inputFormat = argv[start];

					break;

				case 'o':
					if (++start >= argc)
					{
						writer.write ("error: missing output stream format\n");

						return 1;
					}

					outputFormat = argv[start];

					break;

				case 'p':
					progress = true;

					break;

				default:
					writer
						.write ("error: unknown option '")
						.write (*argument)
						.write ("'\n");

					return 1;
			}
		}
	}

	if (!calculator.parse (lookup, calculatorExpression) ||
	    !filter.parse (lookup, filterCondition) ||
	    !input.parse (inputFormat) ||
	    !output.parse (outputFormat))
		return 1;

	printer = output.create ();

	if (!printer)
	{
		writer.write ("error: cannot create printer\n");

		return 1;
	}

	initialize (table, filter, calculator);
	process (table, input, lookup, progress, argv + start, argc - start);

	printer->print (out, table);

	delete printer;

	return 0;
}

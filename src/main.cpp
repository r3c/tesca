
#include <getopt.h>
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

struct option longOptions[] =
{
	{"filter",		required_argument,	0,	'f' },
	{"help",		no_argument,		0,	'h' },
	{"input",		required_argument,	0,	'i' },
	{"output",		required_argument,	0,	'o' },
	{"progress",	no_argument,		0,	'p' },
	{0,				0,					0,	0 }
};

void initialize (Arithmetic::Table& table, const Expression::Filter& filter, Expression::Calculator& calculator)
{
	table.reset (filter.getCondition (), calculator.getColumns (), calculator.getSlots ());
}

void loading (FormatWriter& writer, const char* caption, const Provision::Reader::Progress& progress)
{
	static const Int32u captionWidth = 30;
	static const Int32u meterWidth = 25;

	Int32u i;
	Int32u u;

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

void process (Arithmetic::Table& table, const Provision::Input& input, const Provision::Lookup& lookup, bool progress, char* sources[], int length)
{
	const char* caption;
	Provision::Reader* reader;
	FileIStream source;
	Int8u status;
	FormatWriter writer (err);

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
						.write (")\n");
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

int main (int argc, char* argv[])
{
	Expression::Calculator calculator;
	const char* calculatorExpression;
	FormatWriter console (out);
	Expression::Filter filter;
	const char* filterCondition;
	Provision::Input input;
	const char* inputFormat;
	Provision::Lookup lookup;
	int option;
	Render::Output output;
	const char* outputFormat;
	Render::Printer* printer;
	bool progress;
	Arithmetic::Table table;
	FormatWriter writer (err);

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

	while (true)
	{
		option = getopt_long (argc, argv, "f:hi:o:p", longOptions, NULL);

		if (option == -1)
			break;

		switch (option)
		{
			case 'f':
				filterCondition = optarg;

				break;

			case 'h':
				console
					.write ("usage: tesca [-f <filter>] [-h] [-i <format>] [-o <format>] [-p] <expr> [<file> [<file>...]]\n")
					.write ("  -f: filter condition, e.g. 'len(_0) >= 3'\n")
					.write ("  -h: display help and exit")
					.write ("  -i: input stream format, e.g. 'csv'\n")
					.write ("  -o: output stream format, e.g. 'csv'\n")
					.write ("  -p: display progress bar\n")
					.write ("  <expr>: calculator expression, e.g. '_0: name, sum(_1): duration'\n")
					.write ("  <file>: path to input file(s)\n");

				return 0;

			case 'i':
				inputFormat = optarg;

				break;

			case 'o':
				outputFormat = optarg;

				break;

			case 'p':
				progress = true;

				break;

			case ':':
				writer
					.write ("error: missing argument for option '")
					.write (argv[optind])
					.write ("'\n");

				return 1;

			default:
				writer
					.write ("error: unknown option '")
					.write (argv[optind])
					.write ("'\n");

				return 1;
		}
	}

	if (optind >= argc)
	{
		writer.write ("error: missing calculator expression\n");

		return 1;
	}

	calculatorExpression = argv[optind++];

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
	process (table, input, lookup, progress, argv + optind, argc - optind);

	printer->print (out, table);

	delete printer;

	return 0;
}

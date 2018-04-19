
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

void loading (FormatWriter& error, const char* caption, const Provision::Reader::Progress& progress)
{
	static const Int32u captionWidth = 30;
	static const Int32u meterWidth = 25;

	Int32u i;
	Int32u u;

	error.write ('\r');

	for (i = 0; i < captionWidth && *caption != '\0'; ++i)
		error.write (*caption++);

	for (; i < captionWidth; ++i)
		error.write (' ');

	error
		.write (" [");

	u = progress.read * meterWidth / progress.size;

	for (i = 0; i < u; ++i)
		error.write ('#');

	for (i = u; i < meterWidth; ++i)
		error.write ('-');

	error
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
	FormatWriter error (err);

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
				reader->onError ().bind ([&] (const string& message)
				{
					if (status > 1)
						error.write ("\n");

					error
						.write ("warning: reader error(")
						.write (message)
						.write (")\n");
				});

				reader->onRead ().bind ([&] (const Provision::Reader::Progress& progress)
				{
					if (status > 0 && progress.size > 0)
					{
						loading (error, caption, progress);

						status = 2;
					}
				});

				while (reader->next ())
					table.push (reader->current ());

				if (status > 1)
				{
					error
						.write ("\n")
						.flush ();
				}

				delete reader;
			}
			else
				error.write ("error: cannot create reader\n");
		}
		else
		{
			error
				.write ("error: cannot open '")
				.write (caption)
				.write ("' for reading\n");
		}
	}
}

int main (int argc, char* argv[])
{
	FormatWriter console (out);
	FormatWriter error (err);

	Expression::Calculator calculator;
	Expression::Filter filter;
	Provision::Input input;
	Provision::Lookup lookup;
	Render::Output output;
	Render::Printer* printer;
	Arithmetic::Table table;

	const char* filterCondition = "true";
	const char* inputFormat = "csv";
	const char* outputFormat = "pretty";
	bool progress = false;

	while (true)
	{
		int option = getopt_long (argc, argv, "f:hi:o:p", longOptions, NULL);

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
				error
					.write ("error: missing argument for option '")
					.write (argv[optind])
					.write ("'\n");

				return 1;

			default:
				error
					.write ("error: unrecognized option '")
					.write (argv[optind])
					.write ("'\n");

				return 1;
		}
	}

	if (optind >= argc)
	{
		error.write ("error: missing calculator expression\n");

		return 1;
	}

	calculator.onError ().bind ([&] (const string& message)
	{
		error
			.write ("error: invalid calculator expression (")
			.write (message)
			.write (")\n");
	});

	filter.onError ().bind ([&] (const string& message)
	{
		error
			.write ("error: invalid filter condition (")
			.write (message)
			.write (")\n");
	});

	input.onError ().bind ([&] (const string& message)
	{
		error
			.write ("error: invalid input format (")
			.write (message)
			.write (")\n");
	});

	output.onError ().bind ([&] (const string& message)
	{
		error
			.write ("error: invalid output format (")
			.write (message)
			.write (")\n");
	});

	if (!calculator.parse (lookup, argv[optind++]) ||
	    !filter.parse (lookup, filterCondition) ||
	    !input.parse (inputFormat) ||
	    !output.parse (outputFormat))
		return 1;

	printer = output.create ();

	if (!printer)
	{
		error.write ("error: cannot create printer\n");

		return 1;
	}

	initialize (table, filter, calculator);
	process (table, input, lookup, progress, argv + optind, argc - optind);

	printer->print (out, table);

	delete printer;

	return 0;
}

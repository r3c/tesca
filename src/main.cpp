
#include <string>
#include <vector>
#include "../lib/cxxopts/include/cxxopts.hpp"
#include "arithmetic/table.hpp"
#include "expression/calculator.hpp"
#include "expression/filter.hpp"
#include "provision/input.hpp"
#include "provision/lookup.hpp"
#include "render/output.hpp"

using namespace Glay;
using namespace Glay::Pipe;
using namespace Tesca;
using namespace std;

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

void process (Arithmetic::Table& table, const Provision::Input& input, const Provision::Lookup& lookup, bool progress, const vector<string>& sources)
{
	const char* caption;
	Provision::Reader* reader;
	FileIStream source;
	Int8u status;
	FormatWriter error (err);

	status = progress ? 1 : 0;

	for (Size index = 0; index < sources.size () || index == 0; ++index)
	{
		if (index < sources.size ())
		{
			const char* path = sources[index].c_str ();

			source.open (path);

			caption = path;
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

	bool progress;
	vector<string> sources;

	{
		cxxopts::Options options ("Tesca", "Text Stream Calculator");

		options.add_options ()
			("expression", "Calculator expression", cxxopts::value<string> ())
			("sources", "Input file names (read from stdin if none specified)", cxxopts::value<vector<string>> ())
			("f,filter", "Filter rows with predicate, e.g. 'len(_0) >= 3'", cxxopts::value<string> ()->default_value ("true"))
			("h,help", "Display help and exit")
			("i,input", "Set input format and options, e.g. 'json'", cxxopts::value<string> ()->default_value ("csv"))
			("o,output", "Set output format and options, e.g. 'csv'", cxxopts::value<string> ()->default_value ("pretty"))
			("p,progress", "Display progress bar (when reading from files)", cxxopts::value<bool> ()->default_value ("false"));

		options.parse_positional ({"expression", "sources"});

		auto result = options.parse (argc, argv);

		if (result.count ("help") > 0)
		{
			error.write (options.help ());

			return 0;
		}

		if (result.count ("expression") <= 0)
		{
			error.write ("error: no expression specified, use '-h' option for help\n");

			return 1;
		}

		if (!calculator.parse (lookup, result["expression"].as<string> ().c_str ()) ||
			!filter.parse (lookup, result["filter"].as<string> ().c_str ()) ||
			!input.parse (result["input"].as<string> ().c_str ()) ||
			!output.parse (result["output"].as<string> ().c_str ()))
			return 1;

		progress = result["progress"].as<bool> ();
		sources = result.count ("sources") > 0 ? result["sources"].as<vector<string>> () : vector<string> ();
	}

	printer = output.create ();

	if (!printer)
	{
		error.write ("error: cannot create printer\n");

		return 1;
	}

	initialize (table, filter, calculator);
	process (table, input, lookup, progress, sources);

	printer->print (out, table);

	delete printer;

	return 0;
}

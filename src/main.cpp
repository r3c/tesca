
#include <iostream>
#include <vector>
#include "arithmetic/table.hpp"
#include "expression/formula.hpp"
#include "stream/format.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca;

#include "stream/reader/line.hpp"
#include "stream/row/array.hpp"

class	MyLineReader : public LineReader
{
	public:
		MyLineReader (Glay::Pipe::IStream* stream) :
			LineReader (stream),
			row (0)
		{
		}

		virtual const Row&	current () const
		{
			return this->row;
		}

	protected:
		virtual void	parse (const char* line, Glay::Int32u length)
		{
			cout << "got line: [" << string (line, length) << "]" << endl;
		}

	private:
		ArrayRow	row;
};

//

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

bool	debug_read (Table& table, const Format& format, Pipe::IStream* stream, const Reader::Fields* fields, const char* expression)
{
	Reader*	reader;

	reader = format.create (stream, fields, expression);

	if (!reader)
	{
		cerr << "error: cannot use format \"" << expression << "\"" << endl;

		return false;
	}

	while (reader->next ())
//		table.push (reader->current ());
		;

	delete reader;

	return true;
}

int	main (int argc, char* argv[])
{
	Format	format;
	Formula	formula;

	{
		MyLineReader	r (new Pipe::StandardIStream (&cin));

		while (r.next ())
			;

		return 1;
	}

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
			Pipe::FileIStream	stream (argv[i]);

			if (stream)
				debug_read (table, format, &stream, &formula.getFields (), argv[2]);
			else
				cerr << "error: cannot open file \"" << argv[i] << "\" for reading" << endl;
		}
	}
	else
	{
		Pipe::StandardIStream	stream (&cin);

		if (stream)
			debug_read (table, format, &stream, &formula.getFields (), argv[2]);
		else
			cerr << "error: cannot read from standard output" << endl;
	}

	debug_print (table);
}

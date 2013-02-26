
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

bool	debug_read (Table& table, const Format& format, Pipe::IStream* stream, const Reader::Fields& fields)
{
	Reader*	reader;

	reader = format.create (stream, fields);

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
	Formula				formula;
	Pipe::FileIStream*	stream;
	Table				table;

	if (argc < 3)
	{
		cout << "usage: " << argv[0] << " <input format> <output formula> [<file> [<file>...]]" << endl;

		return 0;
	}

	if (!format.parse (argv[1]))
	{
		cerr << "error: invalid input format" << endl;
	}

	if (!formula.parse (argv[2]))
	{
		cerr << "error: " << formula.getError () << endl;

		return 1;
	}

	table.reset (formula.getColumns ());

	if (argc > 3)
		stream = new Pipe::FileIStream (argv[3]);
	else
		stream = new Pipe::FileIStream (stdin);

	if (*stream)
		debug_read (table, format, stream, formula.getFields ());
	else if (argc > 3)
		cerr << "error: cannot open file \"" << argv[3] << "\" for reading" << endl;
	else
		cerr << "error: cannot open standard input for reading" << endl;

	delete stream;

	debug_print (table);
}


#include <iostream>
#include "arithmetic/column/average.hpp"
#include "arithmetic/column/constant.hpp"
#include "arithmetic/column/field.hpp"
#include "arithmetic/column/sum.hpp"
#include "arithmetic/row.hpp"
#include "arithmetic/table.hpp"
#include "arithmetic/value/number.hpp"
#include "arithmetic/value/string.hpp"
#include "arithmetic/value/void.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca;

ostream&	operator << (ostream& stream, const Value& value)
{
	bool	asBoolean;
	Float64	asNumber;
	string	asString;

	switch (value.getType ())
	{
		case Tesca::Value::ContentType::BOOLEAN:
			value.toBoolean (&asBoolean);

			stream << (asBoolean ? "true" : "false");

			break;

		case Tesca::Value::ContentType::NUMBER:
			value.toNumber (&asNumber);

			stream << asNumber;

			break;

		case Tesca::Value::ContentType::STRING:
			value.toString (&asString);

			stream << "\"" << asString << "\"";

			break;

		case Tesca::Value::ContentType::NONE:
			stream << "void";

			break;

		default:
			stream << "?";

			break;
	}

	return stream;
}

void	debug_print (const Table& table)
{
	for (auto iterator = table.begin (); iterator != table.end (); ++iterator)
	{
		const Slot* const*	slots = iterator->second;

		for (Int32u i = 0; i < 4; ++i)
		{
			const Slot&	slot = *slots[i];

			if (i > 0)
				std::cout << ", ";

			std::cout << "[" << i << "] = " << slot.value ();
		}

		std::cout << std::endl;
	}
}

int	main (int argc, char* argv[])
{
	Column**		columns;
	Row*			row;
	const Value**	values;

	columns = new Column*[4];
	columns[0] = new FieldColumn (0);
	columns[1] = new AverageColumn (new FieldColumn (1));
	columns[2] = new SumColumn (new FieldColumn (1));
	columns[3] = new ConstantColumn (NumberValue (42));

	Table	table (columns, 4);

	values = new const Value*[2];
	values[0] = new StringValue ("A");
	values[1] = new NumberValue (1);

	row = new Row (values);

	table.append (*row);

	delete values[0];
	delete values[1];
	delete [] values;

	debug_print (table);

	values = new const Value*[2];
	values[0] = new StringValue ("A");
	values[1] = new StringValue ("2");

	row = new Row (values);

	table.append (*row);

	delete values[0];
	delete values[1];
	delete [] values;

	debug_print (table);

	values = new const Value*[2];
	values[0] = new NumberValue (8);
	values[1] = new NumberValue (3);

	row = new Row (values);

	table.append (*row);

	delete values[0];
	delete values[1];
	delete [] values;

	debug_print (table);

	values = new const Value*[2];
	values[0] = new StringValue ("8");
	values[1] = new NumberValue (4);

	row = new Row (values);

	table.append (*row);

	delete values[0];
	delete values[1];
	delete [] values;

	debug_print (table);
}

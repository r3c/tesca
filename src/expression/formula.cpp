
#include "formula.hpp"

#include <sstream>
#include "../arithmetic/column/average.hpp"
#include "../arithmetic/column/constant.hpp"
#include "../arithmetic/column/field.hpp"
#include "../arithmetic/column/sum.hpp"
#include "../arithmetic/value/number.hpp"
#include "../arithmetic/value/string.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;

namespace
{
	typedef Tesca::Column*	(*Function) (const Tesca::Formula::Columns&);

	struct	Prototype
	{
		const char*	name;
		Function	function;
		Int32u		count;
	};

	Tesca::Column*	functionAverage (const Tesca::Formula::Columns& arguments)
	{
		return new Tesca::AverageColumn (arguments[0]);
	}

	Tesca::Column*	functionSum (const Tesca::Formula::Columns& arguments)
	{
		return new Tesca::SumColumn (arguments[0]);
	}

	static Prototype	prototypes[] =
	{
		{"avg",	&functionAverage,	1},
		{"sum",	&functionSum,		1}
	};
}

namespace	Tesca
{
	Formula::Formula ()
	{
	}

	Formula::~Formula ()
	{
		this->reset ();
	}

	bool	Formula::fail (const Lexer& lexer, const string& error)
	{
		stringstream	stream;

		stream << error << " at index " << lexer.getIndex ();

		this->error = stream.str ();

		return false;
	}

	const Formula::Columns	Formula::getColumns () const
	{
		return this->columns;
	}

	const string&	Formula::getError () const
	{
		return this->error;
	}

	const Formula::Names	Formula::getNames () const
	{
		return this->names;
	}

	bool	Formula::parse (const char* input)
	{
		Column*	column;
		Lexer	lexer (input);
		string	name;

		while (this->skip (lexer))
		{
			if (!this->readIdentifier (lexer, &name))
				return false;

			this->skip (lexer);

			if (!this->readCharacter (lexer, '='))
				return false;

			this->skip (lexer);

			if (!this->readExpression (lexer, &column))
				return false;

			this->columns.push_back (column);
			this->names.push_back (name);
		}

		return true;
	}

	bool	Formula::readCharacter (Lexer& lexer, const char expected)
	{
		if (lexer.getCurrent () != expected)
			return this->fail (lexer, string ("expected '") + expected + "' character");

		lexer.next ();

		return true;
	}

	bool	Formula::readExpression (Lexer& lexer, Column** column)
	{
		while (true)
		{
			if (!this->readValue (lexer, column))
				return false;

			if (!this->skip (lexer))
				return true;

			switch (lexer.getCurrent ())
			{
				case '+':
					break;

				default:
					return true;
			}
		}
	}

	bool	Formula::readIdentifier (Lexer& lexer, string* output)
	{
		stringstream	buffer;
		bool			read;

		for (read = true; read &&
		     ((lexer.getCurrent () >= '0' && lexer.getCurrent () <= '9') ||
		      (lexer.getCurrent () >= 'A' && lexer.getCurrent () <= 'Z') ||
		      (lexer.getCurrent () >= 'a' && lexer.getCurrent () <= 'z') ||
		      (lexer.getCurrent () == '_')); read = lexer.next ())
			buffer.put (lexer.getCurrent ());

		if (buffer.tellp () <= 0)
			return this->fail (lexer, "expected identifier");

		buffer >> *output;

		return true;
	}

	bool	Formula::readValue (Lexer& lexer, Column** column)
	{
		Columns			arguments;
		stringstream	buffer;
		Float64			number;
		Prototype*		prototype;
		Column*			target;

		// Parse function call
		for (; !lexer.eof () &&
			   ((lexer.getCurrent () >= 'A' && lexer.getCurrent () <= 'Z') ||
				(lexer.getCurrent () >= 'a' && lexer.getCurrent () <= 'z') ||
				(lexer.getCurrent () == '_')); lexer.next ())
			buffer.put (lexer.getCurrent ());

		if (buffer.tellp () > 0)
		{
			if (!this->skip (lexer))
				return this->fail (lexer, "unfinished function call");

			prototype = 0;

			for (Int32u i = sizeof (prototypes) / sizeof (*prototypes); i-- > 0; )
			{
				if (buffer.str () == prototypes[i].name)
				{
					prototype = &prototypes[i];

					break;
				}
			}

			if (!prototype)
				return this->fail (lexer, "unknown function name");

			if (!this->readCharacter (lexer, '('))
				return false;

			while (true)
			{
				if (!this->skip (lexer))
					this->fail (lexer, "unfinished function arguments");

				if (lexer.getCurrent () == ')')
					break;

				if (!this->readValue (lexer, &target))
					return false;

				arguments.push_back (target);
			}

			if (!this->readCharacter (lexer, ')'))
				return false;

			if (arguments.size () != prototype->count)
				return this->fail (lexer, "wrong number of arguments");

			*column = this->store ((*prototype->function) (arguments));

			return true;
		}

		// Parse constant number
		for (; !lexer.eof () &&
		       ((lexer.getCurrent () >= '0' && lexer.getCurrent () <= '9') ||
			    (lexer.getCurrent () == '.')); lexer.next ())
			buffer.put (lexer.getCurrent ());

		if (buffer.tellp () > 0)
		{
			buffer >> number;

			if (buffer.fail ())
				return this->fail (lexer, "invalid number");

			*column = this->store (new ConstantColumn (NumberValue (number)));

			return true;
		}

		// Parse constant string
		if (lexer.getCurrent () == '"')
		{
			while (true)
			{
				if (!lexer.next ())
					return this->fail (lexer, "unfinished string");

				if (lexer.getCurrent () == '"')
					break;

				if (lexer.getCurrent () == '\\' && !lexer.next ())
					return this->fail (lexer, "invalid string escape sequence");

				buffer.put (lexer.getCurrent ());
			}

			lexer.next ();

			*column = this->store (new ConstantColumn (StringValue (buffer.str ())));

			return true;
		}

		// Parse field reference
		if (lexer.getCurrent () == '$')
		{
			if (!lexer.next ())
				return this->fail (lexer, "unfinished field reference");

			for (; !lexer.eof () &&
			       ((lexer.getCurrent () >= '0' && lexer.getCurrent () <= '9') ||
				    (lexer.getCurrent () >= 'A' && lexer.getCurrent () <= 'Z') ||
			        (lexer.getCurrent () >= 'a' && lexer.getCurrent () <= 'z') ||
			        (lexer.getCurrent () == '_')); lexer.next ())
				buffer.put (lexer.getCurrent ());

			*column = this->store (new FieldColumn (buffer.str ()));

			return true;
		}

		return this->fail (lexer, "invalid character");
	}

	void	Formula::reset ()
	{
		for (auto i = this->allocs.begin (); i != this->allocs.end (); ++i)
			delete *i;

		this->allocs.clear ();
		this->columns.clear ();
	}

	bool	Formula::skip (Lexer& lexer)
	{
		while (lexer.getCurrent () <= ' ')
		{
			if (!lexer.next ())
				return false;
		}

		return true;
	}

	Column*	Formula::store (Column* column)
	{
		this->allocs.push_back (column);

		return column;
	}
}

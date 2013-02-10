
#include "formula.hpp"

#include <sstream>
#include "../arithmetic/column/value.hpp"
#include "../arithmetic/reader/constant.hpp"
#include "../arithmetic/reader/field.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;

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

	bool	Formula::parse (const char* input)
	{
		const Aggregator*	aggregator;
		Column*				column;
		string				identifier;
		Lexer				lexer (input);
		Reader*				reader;

		while (this->skip (lexer))
		{
			// Read column identifier
			if (!this->readIdentifier (lexer, &identifier))
				return false;

			this->skip (lexer);

			// Read column aggregator
			if (lexer.getCurrent () == ':')
			{
				if (!lexer.next () || !this->skip (lexer))
					return this->fail (lexer, "missing aggregator name");

				if (!this->readAggregator (lexer, &aggregator))
					return false;

				this->skip (lexer);
			}
			else
				aggregator = 0;

			// Skip expression assignment
			if (!this->readCharacter (lexer, '='))
				return false;

			this->skip (lexer);

			// Parse column expression
			if (!this->readExpression (lexer, &reader))
				return false;

			// Create and push column
			if (aggregator != 0)
				column = (*aggregator->builder) (identifier, reader);
			else
				column = new ValueColumn (identifier, reader);

			this->columns.push_back (column);

			// Skip column separator
			if (!this->skip (lexer))
				break;

			if (!this->readCharacter (lexer, ','))
				return false;
		}

		return true;
	}

	bool	Formula::readAggregator (Lexer& lexer, const Aggregator** output)
	{
		const Aggregator*	aggregator;
		stringstream		buffer;

		for (; !lexer.eof () &&
			   ((lexer.getCurrent () >= 'A' && lexer.getCurrent () <= 'Z') ||
				(lexer.getCurrent () >= 'a' && lexer.getCurrent () <= 'z') ||
				(lexer.getCurrent () == '_')); lexer.next ())
			buffer.put (lexer.getCurrent ());

		aggregator = 0;

		for (Int32u i = 0; Aggregator::aggregators[i].name; ++i)
		{
			if (buffer.str () == Aggregator::aggregators[i].name)
			{
				aggregator = &Aggregator::aggregators[i];

				break;
			}
		}

		if (!aggregator)
			return this->fail (lexer, "unknown aggregator name");

		*output = aggregator;

		return true;
	}

	bool	Formula::readCharacter (Lexer& lexer, const char expected)
	{
		if (lexer.getCurrent () != expected)
			return this->fail (lexer, string ("expected '") + expected + "' character");

		lexer.next ();

		return true;
	}

	bool	Formula::readExpression (Lexer& lexer, Reader** output)
	{
		while (true)
		{
			if (!this->readValue (lexer, output))
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

		for (; !lexer.eof () &&
		     ((lexer.getCurrent () >= '0' && lexer.getCurrent () <= '9') ||
		      (lexer.getCurrent () >= 'A' && lexer.getCurrent () <= 'Z') ||
		      (lexer.getCurrent () >= 'a' && lexer.getCurrent () <= 'z') ||
		      (lexer.getCurrent () == '_')); lexer.next ())
			buffer.put (lexer.getCurrent ());

		if (buffer.tellp () <= 0)
			return this->fail (lexer, "expected identifier");

		buffer >> *output;

		return true;
	}

	bool	Formula::readValue (Lexer& lexer, Reader** output)
	{
		Readers			arguments;
		stringstream	buffer;
		const Function*	function;
		string			identifier;
		Float64			number;
		Reader*			reader;

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

			function = 0;

			for (Int32u i = 0; Function::functions[i].name; ++i)
			{
				if (buffer.str () == Function::functions[i].name)
				{
					function = &Function::functions[i];

					break;
				}
			}

			if (!function)
				return this->fail (lexer, "unknown function name");

			if (!this->readCharacter (lexer, '('))
				return false;

			if (!this->skip (lexer))
				this->fail (lexer, "missing function arguments");

			if (lexer.getCurrent () == ')')
				lexer.next ();
			else
			{
				while (true)
				{
					if (!this->readValue (lexer, &reader))
						return false;

					arguments.push_back (reader);

					if (!this->skip (lexer))
						this->fail (lexer, "missing arguments separator or end of arguments");

					if (lexer.getCurrent () == ')')
					{
						lexer.next ();

						break;
					}

					if (!this->readCharacter (lexer, ','))
						return false;

					if (!this->skip (lexer))
						this->fail (lexer, "missing function argument");
				}
			}

			if (arguments.size () != function->count)
				return this->fail (lexer, "wrong number of arguments");

			*output = (*function->builder) (arguments);

			this->readers.push_back (*output);

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

			*output = new ConstantReader (Variant (number));

			this->readers.push_back (*output);

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

			*output = new ConstantReader (Variant (buffer.str ()));

			this->readers.push_back (*output);

			return true;
		}

		// Parse field reference
		if (lexer.getCurrent () == '$')
		{
			if (!lexer.next ())
				return this->fail (lexer, "unfinished field identifier");

			if (!this->readIdentifier (lexer, &identifier))
				return false;

			*output = new FieldReader (identifier);

			this->readers.push_back (*output);

			return true;
		}

		return this->fail (lexer, "invalid character");
	}

	void	Formula::reset ()
	{
		for (auto i = this->columns.begin (); i != this->columns.end (); ++i)
			delete *i;

		for (auto i = this->readers.begin (); i != this->readers.end (); ++i)
			delete *i;

		this->columns.clear ();
		this->readers.clear ();
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
}

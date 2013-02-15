
#include "formula.hpp"

#include <sstream>
#include "../arithmetic/accessor/constant.hpp"
#include "../arithmetic/accessor/field.hpp"
#include "../arithmetic/accessor/void.hpp"
#include "../arithmetic/column/value.hpp"

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
		const Accessor*		accessor;
		const Aggregator*	aggregator;
		Column*				column;
		bool				first;
		string				identifier;
		Lexer				lexer (input);

		first = true;

		while (this->skip (lexer))
		{
			// Skip columns separator
			if (first)
				first = false;
			else if (!this->readCharacter (lexer, ','))
				return false;
			else if (!this->skip (lexer))
				return this->fail (lexer, "expected column declaration");

			// Read column identifier
			if (!this->readIdentifier (lexer, &identifier))
				return false;

			this->skip (lexer);

			// Read column aggregator
			if (lexer.getCurrent () == ':')
			{
				if (!lexer.next () || !this->skip (lexer))
					return this->fail (lexer, "expected column aggregator");

				if (!this->readAggregator (lexer, &aggregator))
					return false;

				this->skip (lexer);
			}
			else
				aggregator = 0;

			// Read column expression
			if (lexer.getCurrent () == '=')
			{
				if (!lexer.next () || !this->skip (lexer))
					return this->fail (lexer, "expected column expression");

				if (!this->readExpression (lexer, &accessor))
					return false;

				this->skip (lexer);
			}
			else
				accessor = &VoidAccessor::instance;

			// Create and push column
			if (aggregator != 0)
				column = (*aggregator->builder) (identifier, accessor);
			else
				column = new ValueColumn (identifier, accessor);

			this->columns.push_back (column);
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

	bool	Formula::readExpression (Lexer& lexer, const Accessor** output)
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

	bool	Formula::readValue (Lexer& lexer, const Accessor** output)
	{
		const Accessor*	accessor;
		Accessors		arguments;
		stringstream	buffer;
		const Function*	function;
		string			identifier;
		Float64			number;

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
				this->fail (lexer, "expected function arguments");

			if (lexer.getCurrent () == ')')
				lexer.next ();
			else
			{
				while (true)
				{
					if (!this->readValue (lexer, &accessor))
						return false;

					arguments.push_back (accessor);

					if (!this->skip (lexer))
						this->fail (lexer, "expected arguments separator or end of arguments");

					if (lexer.getCurrent () == ')')
					{
						lexer.next ();

						break;
					}

					if (!this->readCharacter (lexer, ','))
						return false;

					if (!this->skip (lexer))
						this->fail (lexer, "expected function argument");
				}
			}

			if (arguments.size () != function->count)
				return this->fail (lexer, "wrong number of arguments");

			*output = (*function->builder) (arguments);

			this->accessors.push_back (*output);

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

			*output = new ConstantAccessor (Variant (number));

			this->accessors.push_back (*output);

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

			*output = new ConstantAccessor (Variant (buffer.str ()));

			this->accessors.push_back (*output);

			return true;
		}

		// Parse field reference
		if (lexer.getCurrent () == '$')
		{
			if (!lexer.next ())
				return this->fail (lexer, "unfinished field identifier");

			if (!this->readIdentifier (lexer, &identifier))
				return false;

			*output = new FieldAccessor (identifier);

			this->accessors.push_back (*output);

			return true;
		}

		return this->fail (lexer, "invalid character");
	}

	void	Formula::reset ()
	{
		for (auto i = this->accessors.begin (); i != this->accessors.end (); ++i)
			delete *i;

		for (auto i = this->columns.begin (); i != this->columns.end (); ++i)
			delete *i;

		this->accessors.clear ();
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
}

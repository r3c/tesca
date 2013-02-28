
#include "parser.hpp"

#include "../arithmetic/accessor/constant.hpp"
#include "../arithmetic/accessor/field.hpp"
#include "../arithmetic/accessor/void.hpp"
#include "../arithmetic/column/value.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Glay::System;
using namespace Tesca::Stream;

namespace	Tesca
{
	namespace	Expression
	{
		Parser::Parser ()
		{
		}

		Parser::~Parser ()
		{
			this->reset ();
		}

		string	Parser::getMessage () const
		{
			return this->message.str ();
		}

		bool	Parser::fail (const Lexer& lexer, const string& error)
		{
			this->message.str ("");
			this->message << error << " at index " << lexer.getIndex ();

			return false;
		}

		bool	Parser::parseAggregator (Lexer& lexer, const Aggregator** output)
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

		bool	Parser::parseCharacter (Lexer& lexer, char expected)
		{
			if (lexer.getCurrent () != expected)
				return this->fail (lexer, string ("expected '") + expected + "' character");

			lexer.next ();

			return true;
		}

		bool	Parser::parseExpression (Lexer& lexer, Lookup& lookup, const Accessor** output)
		{
			while (true)
			{
				if (!this->parseValue (lexer, lookup, output))
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

		bool	Parser::parseIdentifier (Lexer& lexer, string* output)
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

		bool	Parser::parseStatement (Lexer& lexer, Lookup& lookup, Column** column)
		{
			const Accessor*		accessor;
			const Aggregator*	aggregator;
			string				identifier;

			// Read column identifier
			if (!this->parseIdentifier (lexer, &identifier))
				return false;

			this->skip (lexer);

			// Read column expression
			if (lexer.getCurrent () == '=')
			{
				if (!lexer.next () || !this->skip (lexer))
					return this->fail (lexer, "expected column expression");

				if (!this->parseExpression (lexer, lookup, &accessor))
					return false;

				this->skip (lexer);
			}
			else
				accessor = &VoidAccessor::instance;

			// Read column aggregator
			if (lexer.getCurrent () == ':')
			{
				if (!lexer.next () || !this->skip (lexer))
					return this->fail (lexer, "expected column aggregator");

				if (!this->parseAggregator (lexer, &aggregator))
					return false;

				*column = aggregator->builder (identifier, accessor);

				this->skip (lexer);
			}
			else
				*column = new ValueColumn (identifier, accessor);

			this->columns.push_back (*column);

			return true;
		}

		bool	Parser::parseValue (Lexer& lexer, Lookup& lookup, const Accessor** output)
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

				if (!this->parseCharacter (lexer, '('))
					return false;

				if (!this->skip (lexer))
					this->fail (lexer, "expected function arguments");

				if (lexer.getCurrent () == ')')
					lexer.next ();
				else
				{
					while (true)
					{
						if (!this->parseValue (lexer, lookup, &accessor))
							return false;

						arguments.push_back (accessor);

						if (!this->skip (lexer))
							this->fail (lexer, "expected arguments separator or end of arguments");

						if (lexer.getCurrent () == ')')
						{
							lexer.next ();

							break;
						}

						if (!this->parseCharacter (lexer, ','))
							return false;

						if (!this->skip (lexer))
							this->fail (lexer, "expected function argument");
					}
				}

				if (arguments.size () < function->min || (function->max > 0 && arguments.size () > function->max))
				{
					return this->fail (lexer, "wrong number of arguments");
	/*
					if (function->max == 0)
						return this->fail (lexer, string ("function requires at least ") + function->min + " argument(s)");
					else if (function->max == function->min)
						return this->fail (lexer, string ("function requires between ") + function->min + " and " + function->max + " argument(s)");
					else
						return this->fail (lexer, string ("function requires ") + function->min + " argument(s)");
	*/
				}

				*output = function->builder (arguments);

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
				if (!Convert::toFloat64 (&number, buffer.str ().c_str (), buffer.str ().length ()))
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

				if (!this->parseIdentifier (lexer, &identifier))
					return false;

				*output = new FieldAccessor (lookup.set (identifier));

				this->accessors.push_back (*output);

				return true;
			}

			return this->fail (lexer, "invalid character");
		}

		void	Parser::reset ()
		{
			for (auto i = this->accessors.begin (); i != this->accessors.end (); ++i)
				delete *i;

			for (auto i = this->columns.begin (); i != this->columns.end (); ++i)
				delete *i;

			this->accessors.clear ();
			this->columns.clear ();
		}

		bool	Parser::skip (Lexer& lexer)
		{
			while (lexer.getCurrent () <= ' ')
			{
				if (!lexer.next ())
					return false;
			}

			return true;
		}
	}
}

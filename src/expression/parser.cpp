
#include "parser.hpp"

#include <sstream>
#include <stack>
#include "../arithmetic/accessor/binary/number.hpp"
#include "../arithmetic/accessor/constant.hpp"
#include "../arithmetic/accessor/field.hpp"
#include "../arithmetic/accessor/void.hpp"
#include "../arithmetic/column/value.hpp"
#include "constant.hpp"
#include "function.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Glay::System;
using namespace Tesca::Arithmetic;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

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

		const Parser::Error&	Parser::getError () const
		{
			return this->error;
		}

		Parser::Error&	Parser::getError ()
		{
			return this->error;
		}

		bool	Parser::fail (const Lexer& lexer, const string& error)
		{
			stringstream	stream;

			stream << error << " at index " << lexer.getIndex ();

			this->error.fire (stream.str ());

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

			for (auto current = Aggregator::aggregators; current->name; ++current)
			{
				if (buffer.str () == current->name)
				{
					aggregator = current;

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
			BinaryOp				binaryOp;
			stack<BinaryOp>			binaryOps;
			stack<const Accessor*>	operands;
			const Accessor*			value;

			while (true)
			{
				if (lexer.getCurrent () == '(')
				{
					if (!this->parseCharacter (lexer, '(') || !this->parseExpression (lexer, lookup, &value))
						return false;

					this->skip (lexer);

					if (!this->parseCharacter (lexer, ')'))
						return false;
				}
				else
				{
					if (!this->parseValue (lexer, lookup, &value))
						return false;
				}

				operands.push (value);

				if (!this->skip (lexer) || !this->parseOperator (lexer, &binaryOp))
					break;

				if (!lexer.next () || !this->skip (lexer))
					return this->fail (lexer, "expected operand");

				for (; !binaryOps.empty () && binaryOps.top ().first >= binaryOp.first; binaryOps.pop ())
				{
					value = operands.top ();

					operands.pop ();

					value = binaryOps.top ().second (operands.top (), value);

					operands.pop ();
					operands.push (value);

					this->accessors.push_back (value);
				}

				binaryOps.push (binaryOp);
			}

			for (; !binaryOps.empty (); binaryOps.pop ())
			{
				value = operands.top ();

				operands.pop ();

				value = binaryOps.top ().second (operands.top (), value);

				operands.pop ();
				operands.push (value);

				this->accessors.push_back (value);
			}

			*output = operands.top ();

			return true;
		}

		bool	Parser::parseIdentifier (Lexer& lexer, string* output)
		{
			stringstream	buffer;

			for (; !lexer.eof () &&
				 ((lexer.getCurrent () >= '0' && lexer.getCurrent () <= '9') ||
				  (lexer.getCurrent () >= 'A' && lexer.getCurrent () <= 'Z') ||
				  (lexer.getCurrent () >= 'a' && lexer.getCurrent () <= 'z') ||
				  (lexer.getCurrent () == '_') ||
				  (lexer.getCurrent () == '.')); lexer.next ())
				buffer.put (lexer.getCurrent ());

			if (buffer.tellp () <= 0)
				return this->fail (lexer, "expected identifier");

			buffer >> *output;

			return true;
		}

		bool	Parser::parseOperator (Lexer& lexer, BinaryOp* output)
		{
			switch (lexer.getCurrent ())
			{
				case '+':
					*output = make_pair (2, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
					{
						return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
						{
							return Variant (a + b);
						});
					});

					return true;

				case '-':
					*output = make_pair (2, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
					{
						return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
						{
							return Variant (a - b);
						});
					});

					return true;

				case '*':
					*output = make_pair (3, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
					{
						return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
						{
							return Variant (a * b);
						});
					});

					return true;

				case '/':
					*output = make_pair (3, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
					{
						return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
						{
							return b != 0 ? Variant (a / b) : Variant::empty;
						});
					});

					return true;

				case '%':
					*output = make_pair (3, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
					{
						return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
						{
							return b != 0 ? Variant (fmod (a, b)) : Variant::empty;
						});
					});

					return true;

				default:
					return false;
			}
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
			const Constant*	constant;
			const Function*	function;
			string			identifier;
			Float64			number;

			// Parse function call or constant
			for (; !lexer.eof () &&
				   ((lexer.getCurrent () >= 'A' && lexer.getCurrent () <= 'Z') ||
					(lexer.getCurrent () >= 'a' && lexer.getCurrent () <= 'z') ||
					(lexer.getCurrent () == '_')); lexer.next ())
				buffer.put (lexer.getCurrent ());

			if (buffer.tellp () > 0)
			{
				if (this->skip (lexer) && lexer.getCurrent () == '(')
				{
					if (!this->parseCharacter (lexer, '('))
						return false;

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

					if (!this->skip (lexer))
						this->fail (lexer, "expected function arguments");

					while (lexer.getCurrent () != ')')
					{
						if (arguments.size () > 0)
						{
							if (!this->parseCharacter (lexer, ','))
								return false;

							this->skip (lexer);
						}

						if (!this->parseExpression (lexer, lookup, &accessor))
							return false;

						if (!this->skip (lexer))
							this->fail (lexer, "expected next argument or ')'");

						arguments.push_back (accessor);
					}

					lexer.next ();

					if (arguments.size () < function->min || (function->max > 0 && arguments.size () > function->max))
						return this->fail (lexer, "wrong number of arguments");

					*output = function->builder (arguments);
				}
				else
				{
					constant = 0;

					for (Int32u i = 0; Constant::constants[i].name; ++i)
					{
						if (buffer.str () == Constant::constants[i].name)
						{
							constant = &Constant::constants[i];

							break;
						}
					}

					if (!constant)
						return this->fail (lexer, "unknown constant name");

					*output = new ConstantAccessor (constant->builder ());
				}

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

			return this->fail (lexer, "expected value");
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

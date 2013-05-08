
#include "parser.hpp"

#include <sstream>
#include <stack>
#include "../arithmetic/accessor/binary/callback.hpp"
#include "../arithmetic/accessor/binary/number.hpp"
#include "../arithmetic/accessor/logical/and.hpp"
#include "../arithmetic/accessor/logical/or.hpp"
#include "../arithmetic/accessor/unary/boolean.hpp"
#include "../arithmetic/accessor/unary/number.hpp"
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

			if (lexer.getType () != Lexer::CONSTANT)
				return this->fail (lexer, "expected aggregator name");

			aggregator = 0;

			for (auto current = Aggregator::aggregators; current->name; ++current)
			{
				if (lexer.getCurrent () == current->name)
				{
					aggregator = current;

					break;
				}
			}

			if (!aggregator)
				return this->fail (lexer, "unknown aggregator name");

			*output = aggregator;

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
				switch (lexer.getType ())
				{
					case Lexer::PLUS:
						lexer.next ();

						if (!this->parseExpression (lexer, lookup, &value))
							return false;

						break;

					case Lexer::MINUS:
						lexer.next ();

						if (!this->parseExpression (lexer, lookup, &value))
							return false;

						value = new NumberUnaryAccessor (value, [] (Float64 number)
						{
							return Variant (-number);
						});

						this->accessors.push_back (value);

						break;

					case Lexer::NOT:
						lexer.next ();

						if (!this->parseExpression (lexer, lookup, &value))
							return false;

						value = new BooleanUnaryAccessor (value, [] (bool value)
						{
							return Variant (!value);
						});

						this->accessors.push_back (value);

						break;

					case Lexer::PARENTHESIS_BEGIN:
						lexer.next ();

						if (!this->parseExpression (lexer, lookup, &value) ||
						    !this->parseType (lexer, Lexer::PARENTHESIS_END, "closing parenthesis"))
							return false;

						break;

					default:
						if (!this->parseValue (lexer, lookup, &value))
							return false;

						break;
				}

				operands.push (value);

				switch (lexer.getType ())
				{
					case Lexer::AMPERSAND:
						binaryOp = make_pair (1, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new AndLogicalAccessor (lhs, rhs);
						});

						break;

					case Lexer::DIFFERENT:
						binaryOp = make_pair (2, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new CallbackBinaryAccessor (lhs, rhs, [] (const Variant& a, const Variant& b)
							{
								return Variant (a != b);
							});
						});

						break;

					case Lexer::DIVIDE:
						binaryOp = make_pair (4, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
							{
								return b != 0 ? Variant (a / b) : Variant::empty;
							});
						});

						break;

					case Lexer::EQUAL:
						binaryOp = make_pair (2, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new CallbackBinaryAccessor (lhs, rhs, [] (const Variant& a, const Variant& b)
							{
								return Variant (a == b);
							});
						});

						break;

					case Lexer::GREATER_EQUAL:
						binaryOp = make_pair (2, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new CallbackBinaryAccessor (lhs, rhs, [] (const Variant& a, const Variant& b)
							{
								return Variant (a >= b);
							});
						});

						break;

					case Lexer::GREATER_THAN:
						binaryOp = make_pair (2, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new CallbackBinaryAccessor (lhs, rhs, [] (const Variant& a, const Variant& b)
							{
								return Variant (a > b);
							});
						});

						break;

					case Lexer::LOWER_EQUAL:
						binaryOp = make_pair (2, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new CallbackBinaryAccessor (lhs, rhs, [] (const Variant& a, const Variant& b)
							{
								return Variant (a <= b);
							});
						});

						break;

					case Lexer::LOWER_THAN:
						binaryOp = make_pair (2, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new CallbackBinaryAccessor (lhs, rhs, [] (const Variant& a, const Variant& b)
							{
								return Variant (a < b);
							});
						});

						break;

					case Lexer::MINUS:
						binaryOp = make_pair (3, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
							{
								return Variant (a - b);
							});
						});

						break;

					case Lexer::MODULO:
						binaryOp = make_pair (4, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
							{
								return b != 0 ? Variant (fmod (a, b)) : Variant::empty;
							});
						});

						break;

					case Lexer::MULTIPLY:
						binaryOp = make_pair (4, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
							{
								return Variant (a * b);
							});
						});

						break;

					case Lexer::PIPE:
						binaryOp = make_pair (1, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new OrLogicalAccessor (lhs, rhs);
						});

						break;

					case Lexer::PLUS:
						binaryOp = make_pair (3, [] (const Accessor* lhs, const Accessor* rhs) -> Accessor*
						{
							return new NumberBinaryAccessor (lhs, rhs, [] (Float64 a, Float64 b)
							{
								return Variant (a + b);
							});
						});

						break;

					default:
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

				lexer.next ();

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
		}

		bool	Parser::parseStatement (Lexer& lexer, Lookup& lookup, Column** column)
		{
			const Accessor*		accessor;
			const Aggregator*	aggregator;
			string				identifier;

			// Read column identifier
			identifier = lexer.getCurrent ();

			if (!this->parseType (lexer, Lexer::CONSTANT, "column identifier"))
				return false;

			// Read column expression
			if (lexer.getType () == Lexer::EQUAL)
			{
				lexer.next ();

				if (!this->parseExpression (lexer, lookup, &accessor))
					return false;
			}
			else
				accessor = &VoidAccessor::instance;

			// Read column aggregator
			if (lexer.getType () == Lexer::COLON)
			{
				lexer.next ();

				if (!this->parseAggregator (lexer, &aggregator))
					return false;

				*column = aggregator->builder (identifier, accessor);
			}
			else
				*column = new ValueColumn (identifier, accessor);

			this->columns.push_back (*column);

			return true;
		}

		bool	Parser::parseType (Lexer& lexer, Lexer::Lexem type, const char* expected)
		{
			if (lexer.getType () != type)
				return this->fail (lexer, string ("expected ") + expected);

			lexer.next ();

			return true;
		}

		bool	Parser::parseValue (Lexer& lexer, Lookup& lookup, const Accessor** output)
		{
			const Accessor*	accessor;
			Accessors		arguments;
			const Constant*	constant;
			const Function*	function;
			string			name;
			Float64			number;

			switch (lexer.getType ())
			{
				case Lexer::CONSTANT:
					name = lexer.getCurrent ();

					lexer.next ();

					if (lexer.getType () == Lexer::PARENTHESIS_BEGIN)
					{
						function = 0;

						for (Int32u i = 0; Function::functions[i].name; ++i)
						{
							if (Function::functions[i].name == name)
							{
								function = &Function::functions[i];

								break;
							}
						}

						if (!function)
							return this->fail (lexer, string ("unknown function name '") + lexer.getCurrent () + "'");

						lexer.next ();

						while (lexer.getType () != Lexer::PARENTHESIS_END)
						{
							if (arguments.size () > 0 && !this->parseType (lexer, Lexer::COMMA, "argument separator"))
								return false;

							if (!this->parseExpression (lexer, lookup, &accessor))
								return false;

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
							if (Constant::constants[i].name == name)
							{
								constant = &Constant::constants[i];

								break;
							}
						}

						if (!constant)
							return this->fail (lexer, "unknown constant name");

						*output = new ConstantAccessor (constant->value);
					}

					break;

				case Lexer::NUMBER:
					if (!Convert::toFloat (&number, lexer.getCurrent ().c_str (), lexer.getCurrent ().length ()))
						return this->fail (lexer, "invalid number");

					*output = new ConstantAccessor (Variant (number));

					lexer.next ();

					break;

				case Lexer::REFERENCE:
					*output = new FieldAccessor (lookup.store (lexer.getCurrent ().c_str ()));

					lexer.next ();

					break;

				case Lexer::STRING:
					*output = new ConstantAccessor (Variant (lexer.getCurrent ()));

					lexer.next ();

					break;

				default:
					this->fail (lexer, "unexpected character");

					return false;
			}

			this->accessors.push_back (*output);

			return true;
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
	}
}

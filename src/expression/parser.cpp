#include <iostream>
#include "parser.hpp"

#include <cmath>
#include <sstream>
#include <stack>
#include "../arithmetic/column.hpp"
#include "../arithmetic/extractor/binary.hpp"
#include "../arithmetic/extractor/logical/and.hpp"
#include "../arithmetic/extractor/logical/or.hpp"
#include "../arithmetic/extractor/constant.hpp"
#include "../arithmetic/extractor/field.hpp"
#include "../arithmetic/extractor/unary.hpp"
#include "../arithmetic/extractor/void.hpp"
#include "constant.hpp"
#include "function.hpp"
#include "wrapper.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::Pipe;
using namespace Glay::System;
using namespace Tesca::Arithmetic;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Expression
	{
		Parser::Parser ()
		{
		}

		Parser::~Parser ()
		{
			this->reset ();
		}

		Parser::Error const& Parser::onError () const
		{
			return this->error;
		}

		Parser::Error& Parser::onError ()
		{
			return this->error;
		}

		bool Parser::fail (Lexer const& lexer, const string& error)
		{
			stringstream stream;

			stream << error << " at index " << lexer.getIndex ();

			this->error.fire (stream.str ());

			return false;
		}

		bool Parser::parseExpression (Lexer& lexer, Lookup& lookup, Int32u* slot, Extractor const** output)
		{
			BinaryOp binaryOp;
			stack<BinaryOp> binaryOps;
			stack<Extractor const*> operands;
			Extractor const* value;

			while (true)
			{
				switch (lexer.getLexemType ())
				{
					case Lexer::PLUS:
						lexer.next ();

						if (!this->parseExpression (lexer, lookup, slot, &value))
							return false;

						break;

					case Lexer::MINUS:
						lexer.next ();

						if (!this->parseExpression (lexer, lookup, slot, &value))
							return false;

						value = new UnaryExtractor (value, "minus", wrapNumber ([] (Float64 number)
						{
							return Variant (-number);
						}));

						this->extractors.push_back (value);

						break;

					case Lexer::NOT:
						lexer.next ();

						if (!this->parseExpression (lexer, lookup, slot, &value))
							return false;

						value = new UnaryExtractor (value, "not", wrapBoolean ([] (bool value)
						{
							return Variant (!value);
						}));

						this->extractors.push_back (value);

						break;

					case Lexer::PARENTHESIS_BEGIN:
						lexer.next ();

						if (!this->parseExpression (lexer, lookup, slot, &value) ||
						    !this->parseLexemType (lexer, Lexer::PARENTHESIS_END, "closing parenthesis"))
							return false;

						break;

					default:
						if (!this->parseValue (lexer, lookup, slot, &value))
							return false;

						break;
				}

				operands.push (value);

				switch (lexer.getLexemType ())
				{
					case Lexer::AMPERSAND:
						binaryOp = make_pair (1, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new AndLogicalExtractor (lhs, rhs);
						});

						break;

					case Lexer::DIFFERENT:
						binaryOp = make_pair (2, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "ne", [] (Variant const& a, Variant const& b)
							{
								return Variant (a != b);
							});
						});

						break;

					case Lexer::DIVIDE:
						binaryOp = make_pair (4, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "div", wrapNumber ([] (Float64 lhs, Float64 rhs)
							{
								return rhs != 0 ? Variant (lhs / rhs) : Variant::empty;
							}));
						});

						break;

					case Lexer::EQUAL:
						binaryOp = make_pair (2, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "eq", [] (Variant const& a, Variant const& b)
							{
								return Variant (a == b);
							});
						});

						break;

					case Lexer::GREATER_EQUAL:
						binaryOp = make_pair (2, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "ge", [] (Variant const& a, Variant const& b)
							{
								return Variant (a >= b);
							});
						});

						break;

					case Lexer::GREATER_THAN:
						binaryOp = make_pair (2, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "gt", [] (Variant const& a, Variant const& b)
							{
								return Variant (a > b);
							});
						});

						break;

					case Lexer::LOWER_EQUAL:
						binaryOp = make_pair (2, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "le", [] (Variant const& a, Variant const& b)
							{
								return Variant (a <= b);
							});
						});

						break;

					case Lexer::LOWER_THAN:
						binaryOp = make_pair (2, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "lt", [] (Variant const& a, Variant const& b)
							{
								return Variant (a < b);
							});
						});

						break;

					case Lexer::MINUS:
						binaryOp = make_pair (3, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "minus", wrapNumber ([] (Float64 lhs, Float64 rhs)
							{
								return Variant (lhs - rhs);
							}));
						});

						break;

					case Lexer::MODULO:
						binaryOp = make_pair (4, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "mod", wrapNumber ([] (Float64 lhs, Float64 rhs)
							{
								return rhs != 0 ? Variant (fmod (lhs, rhs)) : Variant::empty;
							}));
						});

						break;

					case Lexer::MULTIPLY:
						binaryOp = make_pair (4, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "mul", wrapNumber ([] (Float64 lhs, Float64 rhs)
							{
								return Variant (lhs * rhs);
							}));
						});

						break;

					case Lexer::PIPE:
						binaryOp = make_pair (1, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new OrLogicalExtractor (lhs, rhs);
						});

						break;

					case Lexer::PLUS:
						binaryOp = make_pair (3, [] (Extractor const* lhs, Extractor const* rhs) -> Extractor*
						{
							return new BinaryExtractor (lhs, rhs, "plus", wrapNumber ([] (Float64 lhs, Float64 rhs)
							{
								return Variant (lhs + rhs);
							}));
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

							this->extractors.push_back (value);
						}

						if (operands.top ()->getFlags () == 0)
							return this->fail (lexer, "inconsistent expression");

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

					this->extractors.push_back (value);
				}

				binaryOps.push (binaryOp);
			}
		}

		bool Parser::parseIdentifier (Lexer& lexer, string* output)
		{
			if (lexer.getLexemType () != Lexer::IDENTIFIER)
				return this->fail (lexer, "expected column identifier");

			*output = lexer.getLexemText ();

			lexer.next ();

			return true;
		}

		bool Parser::parseLexemType (Lexer& lexer, Lexer::LexemType expected, const char* verbose)
		{
			if (lexer.getLexemType () != expected)
				return this->fail (lexer, string ("expected ") + verbose);

			lexer.next ();

			return true;
		}

		bool Parser::parseValue (Lexer& lexer, Lookup& lookup, Int32u* slot, Extractor const** output)
		{
			Extractors arguments;
			string name;

			switch (lexer.getLexemType ())
			{
				case Lexer::IDENTIFIER:
					name = lexer.getLexemText ();

					lexer.next ();

					if (lexer.getLexemType () == Lexer::PARENTHESIS_BEGIN)
					{
						Function const* function = nullptr;

						for (Int32u i = 0; Function::functions[i].name; ++i)
						{
							if (Function::functions[i].name == name)
							{
								function = &Function::functions[i];

								break;
							}
						}

						if (function == nullptr)
							return this->fail (lexer, string ("unknown function name '") + lexer.getLexemText () + "'");

						lexer.next ();

						while (lexer.getLexemType () != Lexer::PARENTHESIS_END)
						{
							if (arguments.size () > 0 && !this->parseLexemType (lexer, Lexer::COMMA, "argument separator"))
								return false;

							Extractor const* argument;

							if (!this->parseExpression (lexer, lookup, slot, &argument))
								return false;

							arguments.push_back (argument);
						}

						lexer.next ();

						if (arguments.size () < function->min || (function->max > 0 && arguments.size () > function->max))
							return this->fail (lexer, "wrong number of arguments");

						*output = function->builder (arguments, slot);
					}
					else
					{
						Constant const* constant = nullptr;

						for (Int32u i = 0; Constant::constants[i].name; ++i)
						{
							if (Constant::constants[i].name == name)
							{
								constant = &Constant::constants[i];

								break;
							}
						}

						if (constant != nullptr)
							*output = new ConstantExtractor (constant->value);
						else
							*output = new FieldExtractor (lookup.store (name), name);
					}

					break;

				case Lexer::NUMBER:
					Float64 number;

					if (!Convert::toFloat (&number, lexer.getLexemText ().data (), lexer.getLexemText ().length ()))
						return this->fail (lexer, "invalid number");

					*output = new ConstantExtractor (Variant (number));

					lexer.next ();

					break;

				case Lexer::STRING:
					*output = new ConstantExtractor (Variant (lexer.getLexemText ()));

					lexer.next ();

					break;

				default:
					this->fail (lexer, "unexpected character");

					return false;
			}

			this->extractors.push_back (*output);

			return true;
		}

		void Parser::reset ()
		{
			for (auto& extractor: this->extractors)
				delete extractor;

			this->extractors.clear ();
		}
	}
}

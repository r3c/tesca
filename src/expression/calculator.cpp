
#include "calculator.hpp"

using namespace std;
using namespace Glay;
using namespace Glay::System;
using namespace Tesca::Arithmetic;
using namespace Tesca::Provision;

namespace Tesca
{
	namespace Expression
	{
		Calculator::Calculator () :
			slots (0)
		{
		}

		Calculator::~Calculator ()
		{
			this->reset ();
		}

		const Calculator::Columns& Calculator::getColumns () const
		{
			return this->columns;
		}

		Int32u Calculator::getSlots () const
		{
			return this->slots;
		}

		const Calculator::Error& Calculator::onError () const
		{
			return this->parser.onError ();
		}

		Calculator::Error& Calculator::onError ()
		{
			return this->parser.onError ();
		}

		bool Calculator::parse (Lookup& lookup, const char* input)
		{
			char buffer[32];
			Column column;
			const Extractor* extractor;
			string key;
			Lexer lexer (input);
			bool next;

			this->reset ();

			for (next = false; lexer.getType () != Lexer::END; next = true)
			{
				// Skip columns separator after first column
				if (next && !this->parser.parseType (lexer, Lexer::COMMA, "column separator"))
					return false;

				// Read column expression
				if (!this->parser.parseExpression (lexer, lookup, &this->slots, &extractor))
					return false;

				// Read column key if any
				if (lexer.getType () == Lexer::NAME)
				{
					lexer.next ();

					if (!this->parser.parseIdentifier (lexer, &key))
						return false;
				}
				else
					key = string (buffer, Convert::toString (buffer, sizeof (buffer) / sizeof (*buffer), this->columns.size ()));

				// Build column and add to list
				this->columns.push_back (Column (key, extractor));
			}

			return true;
		}

		void Calculator::reset ()
		{
			this->columns.clear ();	
			this->parser.reset ();
			this->slots = 0;
		}
	}
}

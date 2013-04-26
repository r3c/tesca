
#include "calculator.hpp"

using namespace std;
using namespace Tesca::Arithmetic;
using namespace Tesca::Provision;

namespace	Tesca
{
	namespace	Expression
	{
		Calculator::Calculator ()
		{
		}

		Calculator::~Calculator ()
		{
			this->reset ();
		}

		const Calculator::Columns&	Calculator::getColumns () const
		{
			return this->columns;
		}

		const Calculator::Error&	Calculator::getError () const
		{
			return this->parser.getError ();
		}

		Calculator::Error&	Calculator::getError ()
		{
			return this->parser.getError ();
		}

		bool	Calculator::parse (Lookup& lookup, const char* input)
		{
			Column*	column;
			Lexer	lexer (input);
			bool	next;

			for (next = false; lexer.getType () != Lexer::END; next = true)
			{
				// Skip columns separator after first column
				if (next && !this->parser.parseType (lexer, Lexer::COMMA, "column separator"))
					return false;

				// Parse column statement and add to list
				if (!this->parser.parseStatement (lexer, lookup, &column))
					return false;

				this->columns.push_back (column);
			}

			return true;
		}

		void	Calculator::reset ()
		{
			this->columns.clear ();	
			this->parser.reset ();
		}
	}
}

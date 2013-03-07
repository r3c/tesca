
#include "formula.hpp"

using namespace std;
using namespace Tesca::Provision;

namespace	Tesca
{
	namespace	Expression
	{
		Formula::Formula ()
		{
		}

		Formula::~Formula ()
		{
			this->reset ();
		}

		const Formula::Columns&	Formula::getColumns () const
		{
			return this->columns;
		}

		const Formula::ErrorEvent&	Formula::getError () const
		{
			return this->parser.getError ();
		}

		Formula::ErrorEvent&	Formula::getError ()
		{
			return this->parser.getError ();
		}

		bool	Formula::parse (Lookup& lookup, const char* input)
		{
			Column*	column;
			Lexer	lexer (input);
			bool	next;

			for (next = false; this->parser.skip (lexer); next = true)
			{
				// Skip columns separator after first column
				if (next)
				{
					if (!this->parser.parseCharacter (lexer, ','))
						return false;

					this->parser.skip (lexer);
				}

				// Parse column statement and add to list
				if (!this->parser.parseStatement (lexer, lookup, &column))
					return false;

				this->columns.push_back (column);
			}

			return true;
		}

		void	Formula::reset ()
		{
			this->columns.clear ();	
			this->parser.reset ();
		}
	}
}

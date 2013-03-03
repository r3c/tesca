
#include "select.hpp"

using namespace std;
using namespace Tesca::Provision;

namespace	Tesca
{
	namespace	Expression
	{
		Select::Select () :
			condition (0)
		{
		}

		Select::~Select ()
		{
			this->reset ();
		}

		const Accessor*	Select::getCondition () const
		{
			return this->condition;
		}

		string	Select::getMessage () const
		{
			return this->parser.getMessage ();
		}

		bool	Select::parse (Lookup& lookup, const char* input)
		{
			Lexer	lexer (input);

			this->parser.skip (lexer);

			if (!this->parser.parseExpression (lexer, lookup, &this->condition))
				return false;

			return true;
		}

		void	Select::reset ()
		{
			this->condition = 0;
			this->parser.reset ();
		}
	}
}


#include "select.hpp"

using namespace std;

namespace	Tesca
{
	namespace	Expression
	{
		Select::Select () :
			accessor (0)
		{
		}

		Select::~Select ()
		{
			this->reset ();
		}

		const Accessor*	Select::getAccessor () const
		{
			return this->accessor;
		}

		string	Select::getMessage () const
		{
			return this->parser.getMessage ();
		}

		bool	Select::parse (Lookup& lookup, const char* input)
		{
			Lexer	lexer (input);

			this->parser.skip (lexer);

			if (!this->parser.parseExpression (lexer, lookup, &this->accessor))
				return false;

			return true;
		}

		void	Select::reset ()
		{
			this->accessor = 0;
			this->parser.reset ();
		}
	}
}

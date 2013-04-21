
#include "filter.hpp"

using namespace std;
using namespace Tesca::Arithmetic;
using namespace Tesca::Provision;

namespace	Tesca
{
	namespace	Expression
	{
		Filter::Filter () :
			condition (0)
		{
		}

		Filter::~Filter ()
		{
			this->reset ();
		}

		const Accessor*	Filter::getCondition () const
		{
			return this->condition;
		}

		const Filter::Error&	Filter::getError () const
		{
			return this->parser.getError ();
		}

		Filter::Error&	Filter::getError ()
		{
			return this->parser.getError ();
		}

		bool	Filter::parse (Lookup& lookup, const char* input)
		{
			Lexer	lexer (input);

			this->parser.skip (lexer);

			if (!this->parser.parseExpression (lexer, lookup, &this->condition))
				return false;

			return true;
		}

		void	Filter::reset ()
		{
			this->condition = 0;
			this->parser.reset ();
		}
	}
}

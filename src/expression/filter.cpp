
#include "filter.hpp"

using namespace std;
using namespace Glay;
using namespace Tesca::Arithmetic;
using namespace Tesca::Provision;

namespace Tesca
{
	namespace Expression
	{
		Filter::Filter () :
			condition (0)
		{
		}

		Filter::~Filter ()
		{
			this->reset ();
		}

		const Extractor* Filter::getCondition () const
		{
			return this->condition;
		}

		const Filter::Error& Filter::onError () const
		{
			return this->parser.onError ();
		}

		Filter::Error& Filter::onError ()
		{
			return this->parser.onError ();
		}

		bool Filter::parse (Lookup& lookup, const char* input)
		{
			Int32u slots;

			Lexer lexer (input);

			if (!this->parser.parseExpression (lexer, lookup, &slots, &this->condition))
				return false;

			return true;
		}

		void Filter::reset ()
		{
			this->condition = 0;
			this->parser.reset ();
		}
	}
}

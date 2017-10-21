
#include "if.hpp"

#include "void.hpp"

using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		IfExtractor::IfExtractor (const Extractor* condition, const Extractor* onTrue, const Extractor* onFalse) :
			condition (condition),
			onFalse (onFalse),
			onTrue (onTrue)
		{
		}

		IfExtractor::IfExtractor (const Extractor* condition, const Extractor* onTrue) :
			condition (condition),
			onFalse (&VoidExtractor::instance),
			onTrue (onTrue)
		{
		}

		Variant IfExtractor::compute (const Aggregator* const* aggregators) const
		{
			bool test;

			if (this->condition->compute (aggregators).toBoolean (&test) && test)
				return this->onTrue->compute (aggregators);
			else
				return this->onFalse->compute (aggregators);
		}

		Variant IfExtractor::extract (const Row& row) const
		{
			bool test;

			if (this->condition->extract (row).toBoolean (&test) && test)
				return this->onTrue->extract (row);
			else
				return this->onFalse->extract (row);
		}

		void IfExtractor::recurse (RecurseCallback callback) const
		{
			callback (this->condition);
			callback (this->onFalse);
			callback (this->onTrue);
		}
	}
}

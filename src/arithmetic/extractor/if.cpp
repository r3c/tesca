
#include "if.hpp"
#include "void.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;
using namespace std;

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

		string IfExtractor::createName (Int32u index) const
		{
			return "if_" + this->condition->createName (index);
		}

		Variant IfExtractor::collect (Aggregator const* const* const aggregators) const
		{
			bool test;

			if (this->condition->collect (aggregators).toBoolean (&test) && test)
				return this->onTrue->collect (aggregators);
			else
				return this->onFalse->collect (aggregators);
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

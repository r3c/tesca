
#include "extractor.hpp"

using namespace Glay;

namespace Tesca
{
	namespace Arithmetic
	{
		Extractor::~Extractor ()
		{
		}

		Int32u Extractor::getFlags () const
		{
			Int32u flags = ~0;

			this->recurse ([&] (const Extractor* accessor)
			{
				flags &= accessor->getFlags ();
			});

			return flags;
		}

		void Extractor::recurse (RecurseCallback) const
		{
		}

		void Extractor::populate (Aggregator** aggregators) const
		{
			this->recurse ([aggregators] (const Extractor* child)
			{
				child->populate (aggregators);
			});
		}

		void Extractor::store (Aggregator** aggregators, const Provision::Row& row) const
		{
			this->recurse ([aggregators, &row] (const Extractor* child)
			{
				child->store (aggregators, row);
			});
		}
	}
}

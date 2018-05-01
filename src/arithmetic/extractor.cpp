
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

		void Extractor::prepare (Aggregator** const aggregators) const
		{
			this->recurse ([aggregators] (const Extractor* child)
			{
				child->prepare (aggregators);
			});
		}

		void Extractor::recurse (RecurseCallback) const
		{
		}

		void Extractor::update (Aggregator** const aggregators, const Provision::Row& row) const
		{
			this->recurse ([aggregators, &row] (const Extractor* child)
			{
				child->update (aggregators, row);
			});
		}
	}
}


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

			this->recurse ([&] (Extractor const* accessor)
			{
				flags &= accessor->getFlags ();
			});

			return flags;
		}

		void Extractor::prepare (Aggregator** aggregators) const
		{
			this->recurse ([aggregators] (Extractor const* child)
			{
				child->prepare (aggregators);
			});
		}

		void Extractor::recurse (RecurseCallback) const
		{
		}

		void Extractor::update (Aggregator* const* aggregators, Provision::Row const& row) const
		{
			this->recurse ([aggregators, &row] (Extractor const* child)
			{
				child->update (aggregators, row);
			});
		}
	}
}

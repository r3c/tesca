
#include "extractor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		Extractor::~Extractor ()
		{
		}

		bool	Extractor::composite () const
		{
			bool	result;

			result = false;

			this->recurse ([&] (const Extractor* accessor)
			{
				result = result || accessor->composite ();
			});

			return result;
		}

		void	Extractor::recurse (RecurseCallback) const
		{
		}

		void	Extractor::populate (Aggregator** aggregators) const
		{
			this->recurse ([aggregators] (const Extractor* child)
			{
				child->populate (aggregators);
			});
		}

		void	Extractor::store (Aggregator** aggregators, const Provision::Row& row) const
		{
			this->recurse ([aggregators, &row] (const Extractor* child)
			{
				child->store (aggregators, row);
			});
		}
	}
}

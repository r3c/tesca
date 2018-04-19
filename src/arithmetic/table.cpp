
#include "table.hpp"

#include "extractor/void.hpp"

using namespace Glay;
using namespace Tesca::Provision;
using namespace Tesca::Storage;

namespace Tesca
{
	namespace Arithmetic
	{
		Table::iterator::iterator (const Columns& columns, const Groups& groups, Groups::const_iterator inner) :
			columns (columns),
			groups (groups),
			inner (inner),
			values (new Variant[columns.size ()])
		{
			if (inner != this->groups.end ())
				this->update ();
		}

		Table::iterator::~iterator ()
		{
			delete [] this->values;
		}

		Table::iterator& Table::iterator::operator ++ ()
		{
			if (++this->inner != this->groups.end ())
				this->update ();

			return *this;
		}

		bool Table::iterator::operator == (const iterator& other)
		{
			return this->inner == other.inner;
		}

		bool Table::iterator::operator != (const iterator& other)
		{
			return this->inner != other.inner;
		}

		Storage::Variant*& Table::iterator::operator * ()
		{
			return this->values;
		}

		void Table::iterator::update ()
		{
			const Aggregator* const* aggregators = this->inner->second;
			const Bucket& bucket = this->inner->first;
			Int32u from = 0;
			Int32u to = 0;

			for (auto i = this->columns.begin (); i != this->columns.end (); ++i)
			{
				auto extractor = i->getExtractor ();

				if (extractor->getFlags () & Extractor::COMPOSITE)
					this->values[to] = extractor->compute (aggregators);
				else
					this->values[to] = bucket[from++];

				++to;
			}
		}

		Table::Table () :
			condition (&VoidExtractor::instance),
			slots (0)
		{
		}

		Table::~Table ()
		{
			this->clear ();
		}

		const Table::Columns& Table::getColumns () const
		{
			return this->columns;
		}

		Int32u Table::getWidth () const
		{
			return this->columns.size ();
		}

		Table::iterator Table::begin () const
		{
			return iterator (this->columns, this->groups, this->groups.begin ());
		}

		Table::iterator Table::end () const
		{
			return iterator (this->columns, this->groups, this->groups.end ());
		}

		void Table::clear ()
		{
			for (auto i = this->groups.begin (); i != this->groups.end (); ++i)
			{
				auto aggregators = i->second;

				for (auto j = this->slots; j-- > 0; )
					delete aggregators[j];

				delete [] aggregators;
			}

			this->condition = &VoidExtractor::instance;
			this->slots = 0;

			this->columns.clear ();
			this->composites.clear ();
			this->groups.clear ();
			this->keys.clear ();
		}

		void Table::push (const Row& row)
		{
			Aggregator** aggregators;		
			Bucket bucket (this->keys.size ());
			bool filter;

			// Select row or exit if it should be discarded
			if (!this->condition->extract (row).toBoolean (&filter) || !filter)
				return;

			// Build bucket from extractors of "key" columns
			for (auto i = this->keys.size (); i-- > 0; )
				bucket.set (i, this->keys[i]->extract (row));

			// Retrieve group from bucket or create it
			auto found = this->groups.find (bucket);

			if (found == this->groups.end ())
			{
				aggregators = new Aggregator*[this->slots];

				for (auto i = this->composites.size (); i-- > 0; )
					this->composites[i]->populate (aggregators);

				this->groups[bucket.keep ()] = aggregators;
			}
			else
				aggregators = found->second;

			// Update aggregators for this column group
			for (auto i = this->composites.size (); i-- > 0; )
				this->composites[i]->store (aggregators, row);
		}

		void Table::reset (const Extractor* condition, const Columns& columns, Int32u slots)
		{
			this->clear ();

			for (auto i = columns.begin (); i != columns.end (); ++i)
			{
				const Extractor* extractor = i->getExtractor ();

				if (extractor->getFlags () & Extractor::COMPOSITE)
					this->composites.push_back (extractor);
				else
					this->keys.push_back (extractor);
			}

			this->columns = columns;
			this->condition = condition;
			this->slots = slots;
		}
	}
}

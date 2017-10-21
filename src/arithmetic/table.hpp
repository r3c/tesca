
#ifndef __TESCA_ARITHMETIC_TABLE_HPP
#define __TESCA_ARITHMETIC_TABLE_HPP

#include <algorithm>
#include <map>
#include <vector>
#include "../../lib/glay/src/include.hpp"
#include "../provision/row.hpp"
#include "aggregator.hpp"
#include "bucket.hpp"
#include "column.hpp"
#include "extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class Table
		{
			public:
				typedef std::vector<Column> Columns;
				typedef std::map<Bucket, Aggregator**> Groups;

				class iterator : public std::iterator<std::input_iterator_tag, Storage::Variant*>
				{
					public:
						iterator (const iterator&);
						iterator (const Columns&, const Groups&, Groups::const_iterator);
						~iterator ();

						iterator& operator = (const iterator&);
						iterator operator ++ (int);
						iterator& operator ++ ();
						bool operator == (const iterator&);
						bool operator != (const iterator&);
						Storage::Variant*& operator * ();

					private:
						void update ();

						const Columns& columns;
						const Groups& groups;
						Groups::const_iterator inner;
						Storage::Variant* values;
				};

				Table (const Table&);
				Table ();
				~Table ();

				Table& operator = (const Table&);

				const Columns& getColumns () const;
				Glay::Int32u getWidth () const;

				iterator begin () const;
				iterator end () const;

				void clear ();
				void push (const Provision::Row&);
				void reset (const Extractor*, const Columns&, Glay::Int32u);

			private:
				typedef std::vector<const Extractor*> Extractors;
				typedef std::vector<Glay::Int32u> Indices;

				Columns columns;
				Extractors composites;
				const Extractor* condition;
				Indices indices;
				Extractors keys;
				Groups groups;
				Glay::Int32u slots;
		};
	}
}

#endif

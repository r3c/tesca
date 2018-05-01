
#ifndef __TESCA_ARITHMETIC_TABLE_HPP
#define __TESCA_ARITHMETIC_TABLE_HPP

#include <algorithm>
#include <map>
#include <vector>
#include "../../lib/glay/src/glay.hpp"
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
						iterator (Columns const&, Groups const&, Groups::const_iterator);
						~iterator ();

						iterator& operator = (const iterator&);
						iterator operator ++ (int);
						iterator& operator ++ ();
						bool operator == (const iterator&);
						bool operator != (const iterator&);
						Storage::Variant*& operator * ();

					private:
						void update ();

						Columns const& columns;
						Groups const& groups;
						Groups::const_iterator inner;
						Storage::Variant* values;
				};

				Table (Table const&);
				Table ();
				~Table ();

				Table& operator = (Table const&);

				Columns const& getColumns () const;
				Glay::Int32u getWidth () const;

				iterator begin () const;
				iterator end () const;

				void clear ();
				void push (Provision::Row const&);
				void reset (Extractor const*, Columns const&, Glay::Int32u);

			private:
				typedef std::vector<Extractor const*> Extractors;
				typedef std::vector<Glay::Int32u> Indices;

				Columns columns;
				Extractors composites;
				Extractor const* condition;
				Indices indices;
				Extractors keys;
				Groups groups;
				Glay::Int32u slots;
		};
	}
}

#endif

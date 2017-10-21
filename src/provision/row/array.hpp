
#ifndef __TESCA_PROVISION_ROW_ARRAY_HPP
#define __TESCA_PROVISION_ROW_ARRAY_HPP

#include <array>
#include "../row.hpp"

namespace Tesca
{
	namespace Provision
	{
		class ArrayRow : public Row
		{
			public:
				ArrayRow (const ArrayRow&);
				ArrayRow (Glay::Int32u);
				virtual ~ArrayRow ();

				ArrayRow& operator = (const ArrayRow&);
				virtual const Storage::Variant& operator [] (Glay::Int32u) const;

				virtual Glay::Int32u getLength () const;

				void clear ();
				bool set (Glay::Int32u, const Storage::Variant&);

			private:
				Glay::Int32u length;
				Storage::Variant* values;
		};
	}
}

#endif

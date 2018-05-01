
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
				ArrayRow (ArrayRow const&);
				ArrayRow (Glay::Int32u);
				virtual ~ArrayRow ();

				ArrayRow& operator = (ArrayRow const&);
				virtual Storage::Variant const& operator [] (Glay::Int32u) const;

				virtual Glay::Int32u getLength () const;

				void clear ();
				bool set (Glay::Int32u, Storage::Variant const&);

			private:
				Glay::Int32u length;
				Storage::Variant* values;
		};
	}
}

#endif

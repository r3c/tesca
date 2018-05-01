
#ifndef __TESCA_PROVISION_ROW_HPP
#define __TESCA_PROVISION_ROW_HPP

#include "../../lib/glay/src/glay.hpp"
#include "../storage/variant.hpp"

namespace Tesca
{
	namespace Provision
	{
		class Row
		{
			public:
				Row (Row const&);
				Row ();
				virtual ~Row ();

				Row& operator = (Row const&);
				virtual Storage::Variant const& operator [] (Glay::Int32u) const = 0;

				virtual Glay::Int32u getLength () const = 0;
		};
	}
}

#endif


#ifndef __TESCA_PROVISION_ROW_HPP
#define __TESCA_PROVISION_ROW_HPP

#include "../../lib/glay/src/glay.hpp"
#include "variant.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	Row
		{
			public:
						Row (const Row&);
						Row ();
				virtual	~Row ();

				Row&					operator = (const Row&);
				virtual const Variant&	operator [] (Glay::Int32u) const = 0;

				virtual Glay::Int32u	getLength () const = 0;
		};
	}
}

#endif


#ifndef __TESCA_PROVISION_READER_HPP
#define __TESCA_PROVISION_READER_HPP

#include <map>
#include "../glay/glay.hpp"
#include "row.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	Reader
		{
			public:
						Reader (const Reader&);
						Reader ();
				virtual	~Reader ();

				Reader&	operator = (const Reader&);

				virtual const Row&	current () const = 0;
				virtual bool		next () = 0;
		};
	}
}

#endif

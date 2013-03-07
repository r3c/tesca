
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

				Glay::Int32u	getErrors () const;

				virtual const Row&	current () const = 0;
				virtual bool		next () = 0;

			protected:
				Glay::Int32u	errors;
		};
	}
}

#endif

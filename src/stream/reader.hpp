
#ifndef __TESCA_READER_HPP
#define __TESCA_READER_HPP

#include "row.hpp"

namespace	Tesca
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

#endif

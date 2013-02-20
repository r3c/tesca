
#ifndef __TESCA_STREAM_READER_HPP
#define __TESCA_STREAM_READER_HPP

#include <map>
#include "../glay/glay.hpp"
#include "row.hpp"

namespace	Tesca
{
	class	Reader
	{
		public:
			typedef std::map<std::string, Glay::Int32u>	Fields;

					Reader (const Reader&);
					Reader ();
			virtual	~Reader ();

			Reader&	operator = (const Reader&);

			virtual const Row&	current () const = 0;
			virtual bool		next () = 0;
	};
}

#endif

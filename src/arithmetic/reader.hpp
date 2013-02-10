
#ifndef __TESCA_READER_HPP
#define __TESCA_READER_HPP

#include "row.hpp"
#include "variant.hpp"

namespace	Tesca
{
	class	Reader
	{
		public:
			virtual Variant	read (const Row&) const = 0;
	};
}

#endif

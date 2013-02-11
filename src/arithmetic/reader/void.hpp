
#ifndef __TESCA_READER_VOID_HPP
#define __TESCA_READER_VOID_HPP

#include "../reader.hpp"

namespace	Tesca
{
	class	VoidReader : public Reader
	{
		public:
			static const VoidReader	instance;

		protected:
			virtual Variant	read (const Row&) const;
	};
}

#endif

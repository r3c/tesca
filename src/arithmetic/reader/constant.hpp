
#ifndef __TESCA_READER_CONSTANT_HPP
#define __TESCA_READER_CONSTANT_HPP

#include "../reader.hpp"

namespace	Tesca
{
	class	ConstantReader : public Reader
	{
		public:
			/**/	ConstantReader (const Variant&);

		protected:
			virtual Variant	read (const Row&) const;

		private:
			Variant	constant;
	};
}

#endif

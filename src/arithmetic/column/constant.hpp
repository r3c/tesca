
#ifndef __TESCA_COLUMN_CONSTANT_HPP
#define __TESCA_COLUMN_CONSTANT_HPP

#include "value.hpp"

namespace	Tesca
{
	class	ConstantColumn : public ValueColumn
	{
		public:
			/**/					ConstantColumn (const Value&);
			virtual					~ConstantColumn ();

		protected:
			virtual const Value&	read (const Row&);

		private:
			const Value*	constant;
	};
}

#endif

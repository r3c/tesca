
#ifndef __TESCA_COLUMN_VALUE_HPP
#define __TESCA_COLUMN_VALUE_HPP

#include "../column.hpp"

namespace	Tesca
{
	class	ValueColumn : public Column
	{
		public:
			/**/					ValueColumn ();

			virtual Slot*			create () const;
			virtual const Value&	key () const;
			virtual void			update (const Row&);
			virtual const Value&	value () const;

		protected:
			virtual const Value&	read (const Row&) = 0;

		private:
			const Value*	current;
	};
}

#endif

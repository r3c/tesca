
#ifndef __TESCA_COLUMN_MAP_HPP
#define __TESCA_COLUMN_MAP_HPP

#include "../column.hpp"

namespace	Tesca
{
	class MapColumn : public Column
	{
		public:
			/**/					MapColumn (Column*);

			virtual Slot*			create () const = 0;
			virtual const Value&	key () const = 0;
			virtual void			update (const Row&);
			virtual const Value&	value () const;

		protected:
			virtual const Value&	map (const Value&) = 0;

		private:
			const Value*	result;
			Column*			source;
	};
}

#endif


#ifndef __TESCA_ROW_ARRAY_HPP
#define __TESCA_ROW_ARRAY_HPP

#include <array>
#include "../row.hpp"

namespace	Tesca
{
	class	ArrayRow : public Row
	{
		public:
			/**/	ArrayRow (const ArrayRow&);
			/**/	ArrayRow (Glay::Int32u);
			virtual	~ArrayRow ();

			ArrayRow&				operator = (const ArrayRow&);
			virtual const Variant&	operator [] (Glay::Int32u) const;
			Variant&				operator [] (Glay::Int32u);

			void	clear ();

		private:
			Variant			dummy;
			Glay::Int32u	size;
			Variant*		values;
	};
}

#endif

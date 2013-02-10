
#ifndef __TESCA_COLUMN_HPP
#define __TESCA_COLUMN_HPP

#include <string>
#include "reader.hpp"
#include "row.hpp"
#include "slot.hpp"
#include "variant.hpp"

namespace	Tesca
{
	class	Column
	{
		public:
			/**/	Column (const Column&);
			/**/	Column (const std::string&, const Reader*);

			Column&	operator = (const Column&);

			const std::string&	getIdentifier () const;

			virtual Slot*		create () const = 0;
			virtual bool		key () const = 0;
			Variant				read (const Row&) const;

		private:
			std::string		identifier;
			const Reader*	reader;
	};
}

#endif


#ifndef __TESCA_ARITHMETIC_COLUMN_HPP
#define __TESCA_ARITHMETIC_COLUMN_HPP

#include <string>
#include "../provision/row.hpp"
#include "../storage/variant.hpp"
#include "accessor.hpp"
#include "slot.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	Column
		{
			public:
						Column (const Column&);
						Column (const std::string&, const Accessor*);
				virtual	~Column ();

				Column&	operator = (const Column&);

				const std::string&	getIdentifier () const;

				virtual Slot*		create () const = 0;
				virtual bool		group () const = 0;
				Storage::Variant	read (const Provision::Row&) const;

			private:
				const Accessor*	accessor;
				std::string		identifier;
		};
	}
}

#endif

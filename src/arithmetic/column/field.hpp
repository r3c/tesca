
#ifndef __TESCA_COLUMN_FIELD_HPP
#define __TESCA_COLUMN_FIELD_HPP

#include <string>
#include "value.hpp"

namespace	Tesca
{
	class	FieldColumn : public ValueColumn
	{
		public:
			/**/					FieldColumn (const std::string&);

		protected:
			virtual const Value&	read (const Row&);

		private:
			std::string	key;
	};
}

#endif

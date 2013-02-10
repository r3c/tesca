
#ifndef __TESCA_READER_FIELD_HPP
#define __TESCA_READER_FIELD_HPP

#include <string>
#include "../reader.hpp"

namespace	Tesca
{
	class	FieldReader : public Reader
	{
		public:
			/**/	FieldReader (const std::string&);

		protected:
			virtual Variant	read (const Row&) const;

		private:
			std::string	identifier;
	};
}

#endif

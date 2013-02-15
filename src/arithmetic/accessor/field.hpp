
#ifndef __TESCA_ACCESSOR_FIELD_HPP
#define __TESCA_ACCESSOR_FIELD_HPP

#include <string>
#include "../accessor.hpp"

namespace	Tesca
{
	class	FieldAccessor : public Accessor
	{
		public:
			/**/	FieldAccessor (const std::string&);

		protected:
			virtual Variant	read (const Row&) const;

		private:
			std::string	identifier;
	};
}

#endif

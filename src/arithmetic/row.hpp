
#ifndef __TESCA_ROW_HPP
#define __TESCA_ROW_HPP

#include <map>
#include <string>
#include "../glay/glay.hpp"
#include "variant.hpp"

namespace	Tesca
{
	class	Row
	{
		public:
			/**/			Row ();
			/**/			Row (const Row&);

			Row&			operator = (const Row&);
			const Variant&	operator [] (std::string) const;

			void			clear ();
			void			push (const std::string&, const Variant&);

		private:
			typedef std::map<std::string, Variant>	Fields;

			Fields	fields;
	};
}

#endif

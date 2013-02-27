
#ifndef __TESCA_ARITHMETIC_LOOKUP_HPP
#define __TESCA_ARITHMETIC_LOOKUP_HPP

#include <map>
#include <string>
#include "../glay/glay.hpp"

namespace	Tesca
{
	class	Lookup
	{
		public:
			typedef std::map<std::string, Glay::Int32u>	Indices;
			typedef Indices::const_iterator				const_iterator;

			Lookup (const Lookup&);
			Lookup ();

			Lookup&	operator = (const Lookup&);

			const_iterator	begin () const;
			const_iterator	end () const;

			Glay::Int32u	count () const;
			bool			find (const std::string&, Glay::Int32u*) const;
			Glay::Int32u	set (const std::string&);

		private:
			Indices	indices;
	};
}

#endif


#ifndef __TESCA_ARITHMETIC_COLUMN_HPP
#define __TESCA_ARITHMETIC_COLUMN_HPP

#include <string>
#include "../provision/row.hpp"
#include "../storage/variant.hpp"
#include "extractor.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	Column
		{
			public:
				Column (const Column&);
				Column (const std::string&, const Extractor*);
				Column ();

				Column&	operator = (const Column&);

				const Extractor*	getExtractor () const;
				const std::string&	getKey () const;

			private:
				const Extractor*	extractor;
				std::string			key;
		};
	}
}

#endif

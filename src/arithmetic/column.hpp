
#ifndef __TESCA_ARITHMETIC_COLUMN_HPP
#define __TESCA_ARITHMETIC_COLUMN_HPP

#include <string>
#include "../provision/row.hpp"
#include "../storage/variant.hpp"
#include "extractor.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class Column
		{
			public:
				Column (Column const&);
				Column (const std::string&, Extractor const*);
				Column ();

				Column& operator = (Column const&);

				Extractor const* getExtractor () const;
				const std::string& getKey () const;

			private:
				Extractor const* extractor;
				std::string key;
		};
	}
}

#endif

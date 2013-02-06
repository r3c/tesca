
#ifndef __TESCA_VALUE_HPP
#define __TESCA_VALUE_HPP

#include <string>
#include "../glay/glay.hpp"

namespace	Tesca
{
	class	Value
	{
		public:
			enum class	ContentType
			{
				NONE,
				BOOLEAN,
				NUMBER,
				STRING
			};

			/**/				Value (const Value&);
			/**/				Value ();

			Value&				operator = (const Value&);

			virtual ContentType	getType () const = 0;

			virtual Value*		clone () const = 0;

			virtual bool		toBoolean (bool*) const = 0;
			virtual bool		toNumber (Glay::Float64*) const = 0;
			virtual bool		toString (std::string*) const = 0;
	};

	bool	operator == (const Value&, const Value&);
	bool	operator != (const Value&, const Value&);
	bool	operator < (const Value&, const Value&);
}

#endif

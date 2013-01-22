
#ifndef __TESCA_VALUE_STRING_HPP
#define __TESCA_VALUE_STRING_HPP

#include "../../glay/glay.hpp"
#include "../value.hpp"

namespace	Tesca
{
	class	StringValue : public Value
	{
		public:
			/**/				StringValue (const std::string&);
			/**/				StringValue (const char*);

			StringValue&		operator = (const StringValue&);

			virtual ContentType	getType () const;

			virtual Value*		clone () const;

			virtual bool		toBoolean (bool*) const;
			virtual bool		toNumber (Glay::Float64*) const;
			virtual bool		toString (std::string*) const;

		private:
			std::string	value;
	};
}

#endif

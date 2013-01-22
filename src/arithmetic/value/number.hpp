
#ifndef __TESCA_VALUE_NUMBER_HPP
#define __TESCA_VALUE_NUMBER_HPP

#include "../../glay/glay.hpp"
#include "../value.hpp"

namespace	Tesca
{
	class	NumberValue : public Value
	{
		public:
			/**/				NumberValue (Glay::Float64);

			NumberValue&		operator = (const NumberValue&);

			virtual ContentType	getType () const;

			virtual Value*		clone () const;

			virtual bool		toBoolean (bool*) const;
			virtual bool		toNumber (Glay::Float64*) const;
			virtual bool		toString (std::string*) const;

		private:
			Glay::Float64	value;
	};
}

#endif

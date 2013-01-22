
#ifndef __TESCA_VALUE_BOOLEAN_HPP
#define __TESCA_VALUE_BOOLEAN_HPP

#include "../../glay/glay.hpp"
#include "../value.hpp"

namespace	Tesca
{
	class	BooleanValue : public Value
	{
		public:
			/**/				BooleanValue (bool);

			BooleanValue&		operator = (const BooleanValue&);

			virtual ContentType	getType () const;

			virtual Value*		clone () const;

			virtual bool		toBoolean (bool*) const;
			virtual bool		toNumber (Glay::Float64*) const;
			virtual bool		toString (std::string*) const;

		private:
			bool	value;
	};
}

#endif

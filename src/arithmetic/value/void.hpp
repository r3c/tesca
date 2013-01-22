
#ifndef __TESCA_VALUE_VOID_HPP
#define __TESCA_VALUE_VOID_HPP

#include "../../glay/glay.hpp"
#include "../value.hpp"

namespace	Tesca
{
	class	VoidValue : public Value
	{
		public:
			static const VoidValue		instance;

			virtual ContentType	getType () const;

			virtual Value*		clone () const;

			virtual bool		toBoolean (bool*) const;
			virtual bool		toNumber (Glay::Float64*) const;
			virtual bool		toString (std::string*) const;

		private:
			/**/	VoidValue ();
	};
}

#endif

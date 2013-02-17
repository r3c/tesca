
#ifndef __TESCA_ACCESSOR_UNARY_STRING_HPP
#define __TESCA_ACCESSOR_UNARY_STRING_HPP

#include "../unary.hpp"

namespace	Tesca
{
	class	StringUnaryAccessor : public UnaryAccessor
	{
		public:
			typedef	Variant	(Callback) (std::string&);

			StringUnaryAccessor (const Accessor*, const Callback*);

			virtual Variant	evaluate (const Variant&) const;

		private:
			Callback*	callback;
	};
}

#endif

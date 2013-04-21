
#ifndef __TESCA_ARITHMETIC_BUCKET_HPP
#define __TESCA_ARITHMETIC_BUCKET_HPP

#include "../../lib/glay/src/include.hpp"
#include "../provision/variant.hpp"

namespace	Tesca
{
	namespace	Arithmetic
	{
		class	Bucket
		{
			public:
				Bucket (const Bucket&);
				Bucket (Glay::Int32u);
				~Bucket ();

				Bucket&					operator = (const Bucket&);
				const Provision::Variant&	operator [] (Glay::Int32u) const;

				Glay::Int32u	getLength () const;

				Glay::Int16s	compare (const Bucket&) const;
				Bucket&			keep ();
				void			set (Glay::Int32u, const Provision::Variant&);

			private:
				Provision::Variant*	buffer;
				Glay::Int32u		length;
		};

		bool	operator < (const Bucket&, const Bucket&);
	}
}

#endif

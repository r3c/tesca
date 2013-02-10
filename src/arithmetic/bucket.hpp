
#ifndef __TESCA_BUCKET_HPP
#define __TESCA_BUCKET_HPP

#include "../glay/glay.hpp"
#include "variant.hpp"

namespace	Tesca
{
	class	Bucket
	{
		public:
			/**/			Bucket (const Bucket&);
			/**/			Bucket (Glay::Int32u);
			/**/			~Bucket ();

			Bucket&			operator = (const Bucket&);
			const Variant&	operator [] (Glay::Int32u) const;

			Glay::Int16s	compare (const Bucket&) const;
			Glay::Int32u	length () const;
			void			set (Glay::Int32u, const Variant&);

		private:
			Variant*		buffer;
			Glay::Int32u	size;
	};

	bool	operator < (const Bucket&, const Bucket&);
}

#endif

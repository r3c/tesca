
#ifndef __TESCA_ARITHMETIC_BUCKET_HPP
#define __TESCA_ARITHMETIC_BUCKET_HPP

#include "../glay/glay.hpp"
#include "../stream/variant.hpp"

namespace	Tesca
{
	class	Bucket
	{
		public:
			Bucket (const Bucket&);
			Bucket (Glay::Int32u);
			~Bucket ();

			Bucket&					operator = (const Bucket&);
			const Stream::Variant&	operator [] (Glay::Int32u) const;

			Glay::Int32u	getLength () const;

			Glay::Int16s	compare (const Bucket&) const;
			Bucket&			keep ();
			void			set (Glay::Int32u, const Stream::Variant&);

		private:
			Stream::Variant*	buffer;
			Glay::Int32u		length;
	};

	bool	operator < (const Bucket&, const Bucket&);
}

#endif

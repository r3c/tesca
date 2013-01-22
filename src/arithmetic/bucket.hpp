
#ifndef __TESCA_BUCKET_HPP
#define __TESCA_BUCKET_HPP

#include "../glay/glay.hpp"
#include "value.hpp"

namespace	Tesca
{
	class	Bucket
	{
		public:
			/**/			Bucket (const Bucket&);
			/**/			Bucket (Glay::Int32u);
			/**/			~Bucket ();

			Bucket&			operator = (const Bucket&);
			const Value&	operator [] (Glay::Int32u) const;

			Glay::Int16s	compare (const Bucket&) const;
			Glay::Int32u	length () const;
			void			set (Glay::Int32u, const Value*);

		private:
			const Value**	buffer;
			Glay::Int32u	size;
	};

	bool	operator < (const Bucket&, const Bucket&);
}

#endif

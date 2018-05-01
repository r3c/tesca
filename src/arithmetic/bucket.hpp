
#ifndef __TESCA_ARITHMETIC_BUCKET_HPP
#define __TESCA_ARITHMETIC_BUCKET_HPP

#include "../../lib/glay/src/glay.hpp"
#include "../storage/variant.hpp"

namespace Tesca
{
	namespace Arithmetic
	{
		class Bucket
		{
			public:
				Bucket (Bucket const&);
				Bucket (Glay::Int32u);
				~Bucket ();

				Bucket& operator = (Bucket const&);
				Storage::Variant const& operator [] (Glay::Int32u) const;

				Glay::Int32u getLength () const;

				Glay::Int16s compare (Bucket const&) const;
				Bucket& keep ();
				void set (Glay::Int32u, Storage::Variant const&);

			private:
				Storage::Variant* buffer;
				Glay::Int32u length;
		};

		bool operator < (Bucket const&, Bucket const&);
	}
}

#endif

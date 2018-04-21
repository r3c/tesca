
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
				Bucket (const Bucket&);
				Bucket (Glay::Int32u);
				~Bucket ();

				Bucket& operator = (const Bucket&);
				const Storage::Variant& operator [] (Glay::Int32u) const;

				Glay::Int32u getLength () const;

				Glay::Int16s compare (const Bucket&) const;
				Bucket& keep ();
				void set (Glay::Int32u, const Storage::Variant&);

			private:
				Storage::Variant* buffer;
				Glay::Int32u length;
		};

		bool operator < (const Bucket&, const Bucket&);
	}
}

#endif

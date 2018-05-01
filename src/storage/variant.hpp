
#ifndef __TESCA_STORAGE_VARIANT_HPP
#define __TESCA_STORAGE_VARIANT_HPP

#include <string>
#include "../../lib/glay/src/glay.hpp"

namespace Tesca
{
	namespace Storage
	{
		class Variant
		{
			public:
				static Variant const empty;

				struct String
				{
					const char* buffer;
					Glay::Size length;
				};

				enum Type
				{
					NONE,
					BOOLEAN,
					NUMBER,
					STRING
				};

				Variant (Variant const&);
				Variant (bool);
				Variant (Glay::Float64);
				Variant (Glay::Int64s);
				Variant (Glay::Int64u);
				Variant (const char*, Glay::Size);
				Variant (const std::string&);
				Variant ();
				~Variant ();

				Variant& operator = (Variant const&);

				Type getType () const;

				Glay::Int32s compare (Variant const&) const;
				Variant& keep ();
				void reset ();

				bool toBoolean (bool*) const;
				bool toNumber (Glay::Float64*) const;
				bool toString (std::string*) const;

			private:
				union Value
				{
					bool boolean;
					Glay::Float64 number;
					String string;
				};

				Value content;
				Glay::Int32u* share;
				Type type;
		};

		bool operator == (Variant const&, Variant const&);
		bool operator != (Variant const&, Variant const&);
		bool operator <= (Variant const&, Variant const&);
		bool operator < (Variant const&, Variant const&);
		bool operator >= (Variant const&, Variant const&);
		bool operator > (Variant const&, Variant const&);
	}
}

#endif

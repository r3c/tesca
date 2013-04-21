
#ifndef __TESCA_STORAGE_VARIANT_HPP
#define __TESCA_STORAGE_VARIANT_HPP

#include <string>
#include "../../lib/glay/src/include.hpp"

namespace	Tesca
{
	namespace	Storage
	{
		class	Variant
		{
			public:
				static const Variant	empty;

				struct	String
				{
					const char*		buffer;
					Glay::Int32u	length;
				};

				enum	Type
				{
					NONE,
					BOOLEAN,
					NUMBER,
					STRING
				};

				Variant (const Variant&);
				Variant (bool);
				Variant (Glay::Float64);
				Variant (Glay::Int32s);
				Variant (Glay::Int32u);
				Variant (const char*, Glay::Int32u);
				Variant (const std::string&);
				Variant ();
				~Variant ();

				Variant&	operator = (const Variant&);

				Glay::Int32s	compare (const Variant&) const;
				Variant&		keep ();
				void			reset ();

				bool	toBoolean (bool*) const;
				bool	toNumber (Glay::Float64*) const;
				bool	toString (std::string*) const;

			private:
				union	Value
				{
					bool			boolean;
					Glay::Float64	number;
					String			string;
				};

				Value			content;
				Glay::Int32u*	share;
				Type			type;
		};

		bool	operator == (const Variant&, const Variant&);
		bool	operator != (const Variant&, const Variant&);
		bool	operator <= (const Variant&, const Variant&);
		bool	operator < (const Variant&, const Variant&);
		bool	operator >= (const Variant&, const Variant&);
		bool	operator > (const Variant&, const Variant&);
	}
}

#endif

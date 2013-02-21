
#ifndef __TESCA_STREAM_VARIANT_HPP
#define __TESCA_STREAM_VARIANT_HPP

#include <string>
#include "../glay/glay.hpp"

namespace	Tesca
{
	class	Variant
	{
		public:
			static const Variant	empty;

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
			Variant (const char*, Glay::Int32u);
			Variant (const char*);
			Variant (const std::string&);			
			Variant ();
			~Variant ();

			Variant&	operator = (const Variant&);

			Glay::Int32s	compare (const Variant&) const;
			void			reset ();

			bool	toBoolean (bool*) const;
			bool	toNumber (Glay::Float64*) const;
			bool	toString (std::string*) const;

		private:
			union	Value
			{
				bool			boolean;
				Glay::Float64	number;
				const char*		string;
			};

			void	init (const char*, Glay::Int32u);

			Glay::Int32u*	share;
			Type			type;
			Value			value;
	};

	bool	operator == (const Variant&, const Variant&);
	bool	operator != (const Variant&, const Variant&);
	bool	operator <= (const Variant&, const Variant&);
	bool	operator < (const Variant&, const Variant&);
	bool	operator >= (const Variant&, const Variant&);
	bool	operator > (const Variant&, const Variant&);
}

#endif

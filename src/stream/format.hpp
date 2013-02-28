
#ifndef __TESCA_STREAM_FORMAT_HPP
#define __TESCA_STREAM_FORMAT_HPP

#include <map>
#include <string>
#include "../glay/glay.hpp"
#include "lookup.hpp"
#include "parser.hpp"
#include "reader.hpp"

namespace	Tesca
{
	namespace	Stream
	{
		class	Format
		{
			public:
						Format (const Format&);
						Format ();
				virtual	~Format ();

				Format&	operator = (const Format&);

				Reader*	create (Glay::Pipe::IStream*, const Lookup&) const;
				bool	parse (const char*);

			private:
				Reader::Config	config;
				const Parser*	parser;
		};
	}
}

#endif

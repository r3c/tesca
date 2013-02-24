
#ifndef __TESCA_STREAM_FORMAT_HPP
#define __TESCA_STREAM_FORMAT_HPP

#include <string>
#include "../glay/glay.hpp"
#include "parser.hpp"
#include "reader.hpp"

namespace	Tesca
{
	class	Format
	{
		public:
					Format (const Format&);
					Format ();
			virtual	~Format ();

			Format&	operator = (const Format&);

			Reader*	create (Glay::Pipe::IStream*, const Reader::Fields*) const;
			bool	parse (const char*);

		private:
			std::string		config;
			const Parser*	parser;
	};
}

#endif

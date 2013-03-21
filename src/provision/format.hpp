
#ifndef __TESCA_PROVISION_FORMAT_HPP
#define __TESCA_PROVISION_FORMAT_HPP

#include <map>
#include <string>
#include "../../lib/glay/src/include.hpp"
#include "config.hpp"
#include "lookup.hpp"
#include "parser.hpp"
#include "reader.hpp"

namespace	Tesca
{
	namespace	Provision
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
				Config			config;
				const Parser*	parser;
		};
	}
}

#endif

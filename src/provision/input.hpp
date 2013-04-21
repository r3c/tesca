
#ifndef __TESCA_PROVISION_INPUT_HPP
#define __TESCA_PROVISION_INPUT_HPP

#include <string>
#include "../../lib/glay/src/include.hpp"
#include "config.hpp"
#include "format.hpp"
#include "lookup.hpp"
#include "reader.hpp"

namespace	Tesca
{
	namespace	Provision
	{
		class	Input
		{
			public:
				typedef Glay::Design::Event<const std::string&>	Error;

						Input (const Input&);
						Input ();
				virtual	~Input ();

				Input&	operator = (const Input&);

				const Error&	getError () const;
				Error&			getError ();

				Reader*	create (Glay::Pipe::IStream*, const Lookup&) const;
				bool	parse (const char*);

			private:
				Config			config;
				Error			error;
				const Format*	format;
		};
	}
}

#endif

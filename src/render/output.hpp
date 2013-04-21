
#ifndef __TESCA_RENDER_OUTPUT_HPP
#define __TESCA_RENDER_OUTPUT_HPP

#include <string>
#include "../../lib/glay/src/include.hpp"
#include "../storage/config.hpp"
#include "format.hpp"
#include "printer.hpp"

namespace	Tesca
{
	namespace	Render
	{
		class	Output
		{
			public:
				typedef Glay::Design::Event<const std::string&>	Error;

						Output (const Output&);
						Output ();
				virtual	~Output ();

				Output&	operator = (const Output&);

				const Error&	getError () const;
				Error&			getError ();

				Printer*	create () const;
				bool		parse (const char*);

			private:
				Storage::Config	config;
				Error			error;
				const Format*	format;
		};
	}
}

#endif

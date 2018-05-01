
#ifndef __TESCA_RENDER_OUTPUT_HPP
#define __TESCA_RENDER_OUTPUT_HPP

#include <string>
#include "../../lib/glay/src/glay.hpp"
#include "../storage/config.hpp"
#include "format.hpp"
#include "printer.hpp"

namespace Tesca
{
	namespace Render
	{
		class Output
		{
			public:
				typedef Glay::Design::Event<const std::string&> Error;

						Output (Output const&);
						Output ();
				virtual ~Output ();

				Output& operator = (Output const&);

				Error const& onError () const;
				Error& onError ();

				Printer* create () const;
				bool parse (const char*);

			private:
				Storage::Config config;
				Error error;
				Format const* format;
		};
	}
}

#endif

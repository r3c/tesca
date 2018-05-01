
#ifndef __TESCA_PROVISION_INPUT_HPP
#define __TESCA_PROVISION_INPUT_HPP

#include <string>
#include "../../lib/glay/src/glay.hpp"
#include "../storage/config.hpp"
#include "format.hpp"
#include "lookup.hpp"
#include "reader.hpp"

namespace Tesca
{
	namespace Provision
	{
		class Input
		{
			public:
				typedef Glay::Design::Event<const std::string&> Error;

				Input (Input const&);
				Input ();
				virtual ~Input ();

				Input& operator = (Input const&);

				Error const& onError () const;
				Error& onError ();

				Reader* create (Glay::Pipe::SeekIStream*, Lookup const&) const;
				bool parse (const char*);

			private:
				Storage::Config config;
				Error error;
				Format const* format;
		};
	}
}

#endif

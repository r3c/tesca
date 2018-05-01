
#ifndef __TESCA_PROVISION_READER_HPP
#define __TESCA_PROVISION_READER_HPP

#include "../../lib/glay/src/glay.hpp"
#include "row.hpp"

namespace Tesca
{
	namespace Provision
	{
		class Reader
		{
			public:
				struct Progress
				{
					Progress (Glay::Int64u, Glay::Int64u);

					Glay::Int64u read;
					Glay::Int64u size;
				};

				typedef Glay::Design::Event<const std::string&> Error;
				typedef Glay::Design::Event<Progress const&> Read;

				Reader (Reader const&);
				Reader ();
				virtual ~Reader ();

				Reader& operator = (Reader const&);

				Error const& onError () const;
				Error& onError ();
				Read const& onRead () const;
				Read& onRead ();

				virtual Row const& current () const = 0;
				virtual bool next () = 0;

			protected:
				Error error;
				Read read;
		};
	}
}

#endif

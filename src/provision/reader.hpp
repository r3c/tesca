
#ifndef __TESCA_PROVISION_READER_HPP
#define __TESCA_PROVISION_READER_HPP

#include "../../lib/glay/src/include.hpp"
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
				typedef Glay::Design::Event<const Progress&> Read;

				Reader (const Reader&);
				Reader ();
				virtual ~Reader ();

				Reader& operator = (const Reader&);

				const Error& onError () const;
				Error& onError ();
				const Read& onRead () const;
				Read& onRead ();

				virtual const Row& current () const = 0;
				virtual bool next () = 0;

			protected:
				Error error;
				Read read;
		};
	}
}

#endif
